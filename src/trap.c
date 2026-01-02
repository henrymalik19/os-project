#include "trap.h"
#include "console.h"
#include "timer.h"
#include "proc.h"

#define INTERRUPT_MASK 0x8000000000000000
#define TRAP_CAUSE_MASK 0xFFF

#define SSI_CAUSE 1 // Supervisor Software Interrupt
#define STI_CAUSE 5 // Supervisor Timer Interrupt

void trap_init()
{
    asm volatile("csrw stvec, %0" : : "r"(trap_vector));
}

long trap_handler(long sp)
{
    current_task->sp_address = sp;
    long scause;
    asm volatile("csrr %0, scause" : "=r"(scause));

    int is_interupt = ((scause & INTERRUPT_MASK) >> 63) == 1;
    int cause_code = scause & TRAP_CAUSE_MASK;

    if (is_interupt)
    {
        if (cause_code == SSI_CAUSE)
        {       
            // kputs("");
            // kprint("INTERRUPT (SSI) CODE: ");
            // kputd(cause_code);

            asm volatile("csrci sip, %0" : : "i"(0x2));
        }
        else if (cause_code == STI_CAUSE)
        {            
            // kputs("");
            // kprint("INTERRUPT (STI) CODE: ");
            // kputd(cause_code);
            timer_init();
            system_ticks++;
        }
        else
        {           
            kputs("");
            kprint("INTERRUPT (UNKNOWN) CODE: ");
            kputd(cause_code);
        }

        task_scheduler();
    }
    else
    {            
        kputs("");
        kprint("EXCEPTION CODE: ");
        kputd(cause_code);
        kprint("PC: ");

        long bad_pc;
        asm volatile("csrr %0, sepc" : "=r"(bad_pc));
        kputh(bad_pc);
        while(1);
    }

    return current_task->sp_address;
}

void intr_enable()
{
    asm volatile(
        "csrs sie,     %0\n\t"
        "csrs sstatus, %1\n\t"
        : 
        : "r"(0x22), "r"(0x2)
    );
}
