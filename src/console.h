#ifndef CONSOLE_H
#define CONSOLE_H

#define ASCII_NUMBER_OFFSET 48
#define ASCII_LETTER_OFFSET 55

// ASCII CHARACTER CODES
#define ASCII_BACKSPACE 0x08
#define ASCII_ENTER 0x0d
#define ASCII_DELETE 0x7f
#define ASCII_SPACE 0x20

// ESCAPE CODES
#define ESCAPE_CLEAR "\x1b[2J"
#define ESCAPE_CURSOR_HOME "\x1b[H"
#define ESCAPE_CURSOR_BACK "\x1b[1D"

void kputs(const char *s);
void kprint(const char *s);
void kputh(unsigned long h);
void kputd(unsigned long d);
long readline(char *buffer, long max_length);
int parse_args(char *line, char **argv);

#endif
