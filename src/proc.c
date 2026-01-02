#include "proc.h"
#include "console.h"
#include "timer.h"

task_t *current_task;
task_t task_table[MAX_TASKS];
long task_stacks[MAX_TASKS][TASK_STACK_SIZE];


void task1_func() {
    while(1) 
    {
        // kprint("\nTask 1 => Current system ticks ");
        // kputd(system_ticks);
        sleep_ms(5000);
    }
}

void task2_func() {
    while(1) 
    {
        // kprint("\nTask 2 => Current system ticks ");
        // kputd(system_ticks);
        sleep_ms(5000);
    }
}

void process_init()
{
    for (long i = 0; i < MAX_TASKS; i++)
    {
        task_table[i].state = TASK_FREE;
    }
    
    task_table[0].id = 0;
    task_table[0].state = TASK_RUNNING;
    current_task = &task_table[0];
}

void task_create(void (*func)())
{
    for (long i = 0; i < MAX_TASKS; i++)
    {
        if (task_table[i].state == TASK_FREE)
        {
            // task_stacks[i][TASK_STACK_SIZE - 31] = 0x120;
            // task_stacks[i][TASK_STACK_SIZE - 32] = (long)func;

            // // ZERO OUT STACK VALUES
            
            // task_table[i].id = i;
            // task_table[i].sp_address = (long)&task_stacks[i][TASK_STACK_SIZE - 32];
            // task_table[i].state = TASK_READY;


            context_t *ctx = (context_t *)&task_stacks[i][TASK_STACK_SIZE - (sizeof(context_t) / 8)];
            ctx->sstatus = 0x120;
            ctx->pc = (long)func;

            // ZERO OUT STACK VALUES
            
            task_table[i].id = i;
            task_table[i].sp_address = (long)ctx;
            task_table[i].state = TASK_READY;

            break;
        }
    }
    
}

void task_scheduler()
{
    task_table[0].state = TASK_READY;
    if (current_task->state == TASK_RUNNING)
    {
        current_task->state = TASK_READY;
    }

    long i = current_task->id + 1;

    while (1)
    {    
        if (i == MAX_TASKS)
        {
            i = 0;
        }

        if (system_ticks >= task_table[i].sleep_until && task_table[i].state == TASK_SLEEPING)
        {
            task_table[i].state = TASK_READY;
        }

        if (task_table[i].state == TASK_READY)
        {
            current_task = &task_table[i];
            current_task->state = TASK_RUNNING;
            break;
        }
        i++;
    }
}

void yield()
{
    asm volatile("csrs sip, %0" : : "i"(0x2));
}

void sleep(long ticks)
{
    current_task->state = TASK_SLEEPING;
    current_task->sleep_until = system_ticks + ticks;
    yield();
}

void sleep_ms(long ms)
{
    long ticks = ((ms * TICKS_PER_SECOND) + 999) / 1000;
    sleep(ticks);
}
