#ifndef SBI_H
#define SBI_H

struct sbiret 
{
    long error;
    long value;
};
typedef struct sbiret sbiret_t;

char sbi_console_getchar();
void sbi_console_putchar(char ch);
sbiret_t sbi_set_timer(long time_value);

#endif
