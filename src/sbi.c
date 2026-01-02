#include "sbi.h"

sbiret_t sbi_call(long arg0, long arg1, long arg2, long arg3, long arg4, long arg5, long fid, long eid) 
{
    register long a0 asm("a0") = arg0;
    register long a1 asm("a1") = arg1;
    register long a2 asm("a2") = arg2;
    register long a3 asm("a3") = arg3;
    register long a4 asm("a4") = arg4;
    register long a5 asm("a5") = arg5;
    register long a6 asm("a6") = fid;
    register long a7 asm("a7") = eid;

    asm volatile (
        "ecall"
        : "+r" (a0), "+r" (a1)
        : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
        : "memory"
    );

    return (sbiret_t){.error = a0, .value = a1};
}

void sbi_console_putchar(char ch) 
{
    sbi_call(ch, 0, 0, 0, 0, 0, 0, 0x01);
}

char sbi_console_getchar() 
{
    sbiret_t SbiReturn = sbi_call(0, 0, 0, 0, 0, 0, 0, 0x02);

    if (SbiReturn.error > 255 || SbiReturn.error < 0)
    {
        return '\0';
    } // a0 Register

    return (char)SbiReturn.error;
}

sbiret_t sbi_set_timer(long time_value)
{
    sbiret_t SbiReturn = sbi_call(time_value, 0, 0, 0, 0, 0, 0, 0x54494D45);
}
