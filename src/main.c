#include "commands.h"
#include "console.h"
#include "string.h"
#include "trap.h"
#include "timer.h"
#include "proc.h"

#define BUFFER_SIZE 128

extern volatile long _KERNEL_BASE;
extern volatile long _KERNEL_END;
extern volatile long _TEXT_START;
extern volatile long _TEXT_END;
extern volatile long _RODATA_START;
extern volatile long _RODATA_END;
extern volatile long _DATA_START;
extern volatile long _DATA_END;
extern volatile long _BSS_START;
extern volatile long _BSS_END;
extern volatile long _STACK_BOTTOM;
extern volatile long _STACK_TOP;
extern volatile long _RAM_START;
extern volatile long _RAM_END;
extern volatile long _HEAP_START;

char input_buffer[BUFFER_SIZE];
char *argv[10]; // TEMP Can handle up to 10 words/arguments

void kernel_main(long hartid, long *dtb_ptr)
{
    process_init();
    task_create(task1_func);
    task_create(task2_func);


    trap_init();
    timer_init();
    intr_enable();

    kputs("\nWelcome to Tiny-Unix!");
    kputs("---------------------\n");

    kprint("Kernel Start Address   0x");
    kputh((long)&_KERNEL_BASE);
    kputs("");

    kprint(".text Start Address    0x");
    kputh((long)&_TEXT_START);
    kputs("");

    kprint(".text End Address      0x");
    kputh((long)&_TEXT_END);
    kputs("");

    kprint(".rodata Start Address  0x");
    kputh((long)&_RODATA_START);
    kputs("");

    kprint(".rodata End Address    0x");
    kputh((long)&_RODATA_END);
    kputs("");

    kprint(".data Start Address    0x");
    kputh((long)&_DATA_START);
    kputs("");

    kprint(".data End Address      0x");
    kputh((long)&_DATA_END);
    kputs("");

    kprint(".bss Start Address     0x");
    kputh((long)&_BSS_START);
    kputs("");

    kprint("stack bottom Address   0x");
    kputh((long)&_STACK_BOTTOM);
    kputs("");

    kprint("stack top Address      0x");
    kputh((long)&_STACK_TOP);
    kputs("");

    kprint(".bss End Address       0x");
    kputh((long)&_BSS_END);
    kputs("");

    kprint("Kernel End Address     0x");
    kputh((long)&_KERNEL_END);
    kputs("");

    kprint("Heap Start Address     0x");
    kputh((long)&_HEAP_START);
    kputs("");

    kprint("Ram Start Address      0x");
    kputh((long)&_RAM_START);
    kputs("");

    kprint("Ram End Address        0x");
    kputh((long)&_RAM_END);
    kputs("");

    while (1) {
        kprint("> ");
        readline(input_buffer, BUFFER_SIZE);
        int argc = parse_args(input_buffer, argv);

        if (argc == 0) continue;
        
        int idx = 0;
        while (cmd_table[idx].name != 0)
        {
            if (strcmp(cmd_table[idx].name, argv[0]) == 0)
            {   
                cmd_table[idx].handler(argc, argv);
            }
            idx++;
        }
    };
    
}
