#ifndef PROC_H
#define PROC_H

#define MAX_TASKS 8
#define TASK_STACK_SIZE 1024

#define TASK_FREE     0  // Slot is empty
#define TASK_READY    1  // Ready to run
#define TASK_RUNNING  2  // Currently on the CPU
#define TASK_SLEEPING 3  // Waiting for a timer or event

typedef struct
{
    long pc;
    long sstatus;

    // General Purpose Registers
    long x3;
    long x4;
    long x5;
    long x6;
    long x7;
    long x8;
    long x9;
    long x10;
    long x11;
    long x12;
    long x13;
    long x14;
    long x15;
    long x16;
    long x17;
    long x18;
    long x19;
    long x20;
    long x21;
    long x22;
    long x23;
    long x24;
    long x25;
    long x26;
    long x27;
    long x28;
    long x29;
    long x30;
    long x31;
    long x1;
} context_t;

typedef struct
{
    long id;
    char state;
    long sp_address;
    long sleep_until;
    context_t context;
} task_t;

extern task_t task_table[MAX_TASKS];
extern task_t *current_task;

void process_init();
void task_create(void (*func)());
void task_scheduler();
void yield();
void sleep(long  ticks);
void sleep_ms(long  ms);

void task1_func();
void task2_func();

#endif
