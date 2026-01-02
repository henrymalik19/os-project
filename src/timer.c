#include "timer.h"
#include "sbi.h"

volatile long system_ticks = 0;

void timer_init()
{
    long time;
    asm volatile("csrr %0, time" : "=r"(time));

    sbi_set_timer(time + (long)(CYCLES_PER_TICK));
    // MAYBE HANDLE ERROR from "sbi_set_timer"
}
