#include "console.h"
#include "sbi.h"

void kprint(const char *s)
{
    int idx = 0;
    while (s[idx] != '\0')
    {
        sbi_console_putchar(s[idx]);
        idx++;
    }
}
void kputs(const char *s)
{
    kprint(s);
    sbi_console_putchar('\n');
}

void kputh(unsigned long h) {
    int idx = 0;

    while (idx < 16)
    {
        unsigned long h_shift = (h >> 60 - (idx * 4)) & 0xF;

        if (h_shift >= 0 && h_shift < 10) 
        {
            sbi_console_putchar(h_shift + ASCII_NUMBER_OFFSET);
        }
        else if (h_shift >= 10 && h_shift < 16)
        {
            sbi_console_putchar(h_shift + ASCII_LETTER_OFFSET);
        }

        idx++;
    }
}

void kputd(unsigned long d)
{
    if (d == 0) { kprint("0"); return; }
    
    char buf[64];
    int idx = 0;
    while (d > 0)
    {
        buf[idx] = (d % 10) + ASCII_NUMBER_OFFSET;
        d /= 10; 

        idx++;
    }
    idx--;

    char rev_buf[64];
    int r_idx = 0;
    while (idx >= 0)
    {    
        rev_buf[r_idx] = buf[idx];
        r_idx++;
        idx--;
    }
    rev_buf[r_idx] = '\0';
     
    kprint(rev_buf);
}

long readline(char *buffer, long max_length)
{
    long idx = 0;
    char c;

    while (idx < (max_length - 1)) 
    {
        c = sbi_console_getchar();

        if (c == -1 || c == '\0')
        {
            continue;
        }

        if (c == ASCII_ENTER)
        {
            sbi_console_putchar('\n');
            break;
        }

        if ((c == ASCII_DELETE) || (c == ASCII_BACKSPACE))
        {
            if (idx == 0) continue;
            
            kprint(ESCAPE_CURSOR_BACK);
            sbi_console_putchar(' ');
            kprint(ESCAPE_CURSOR_BACK);
            idx--;

            continue;
        }

        buffer[idx] = c;
        sbi_console_putchar(buffer[idx]);
        idx++;
    };

    buffer[idx] = '\0';

    return idx;
}

int parse_args(char *line, char **argv)
{
    if (line[0] == '\0') return 0;

    int argc = 0;
    int c_idx = 0;
    int in_word = 0;

    while (1)
    {
        if (line[c_idx] == '\0') break;

        if (line[c_idx] != ASCII_SPACE && in_word == 0)
        {
            argv[argc] = &line[c_idx];

            argc++;
            c_idx++;
            in_word = 1;
            continue;
        }

        if (line[c_idx] == ASCII_SPACE && in_word == 1)
        {
            line[c_idx] = '\0';
            
            c_idx++;
            in_word = 0;

            while (line[c_idx] == ASCII_SPACE)
            {
                c_idx++;
            }

            continue;
        }

        c_idx++;
    }

    return argc;
}
