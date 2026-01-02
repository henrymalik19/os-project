#ifndef TIMER_H
#define TIMER_H

#define CLOCK_FREQ            10000000 // 10Mhz
#define TICKS_PER_SECOND      100
#define CYCLES_PER_TICK       (CLOCK_FREQ / TICKS_PER_SECOND)


extern volatile long system_ticks;

void timer_init();

#endif
