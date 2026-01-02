#include "commands.h"
#include "console.h"
#include "timer.h"
#include "proc.h"

struct command cmd_table[] = { 
    { 
        .name = "help", 
        .description = "Display information about available commands", 
        .handler = do_help 
    },
    { 
        .name = "echo", 
        .description = "Display a line of text passed as arguments", 
        .handler = do_echo 
    },
    { 
        .name = "hang", 
        .description = "Deliberately freeze the system (Test interrupts)", 
        .handler = do_hang 
    },
    { 
        .name = "info", 
        .description = "Display kernel version and hardware boot info", 
        .handler = do_info
    },
    { 
        .name = "uptime", 
        .description = "Display how long the system or a process has been running", 
        .handler = do_uptime
    },
    { 
        .name = "ps", 
        .description = "Display info about all processes", 
        .handler = do_ps
    },
    { 
        .name = 0,
        .description = 0,
        .handler = 0
    }
};

void do_help(int argc, char **argv)
{
    for (int i = 0; cmd_table[i].name != 0; i++)
    {
        kprint("\t");
        kprint(cmd_table[i].name);
        kprint(": ");
        kputs(cmd_table[i].description);
    }
    
}

void do_echo(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (i != 1) 
        {
            kprint(" ");
        }
        kprint(argv[i]);
    }
    kputs("");
}

void do_hang(int argc, char **argv)
{
    kputs("hang");
    while (1);
    
}

void do_info(int argc, char **argv)
{
    kputs("info");
}

void do_uptime(int argc, char **argv)
{
    kprint("System has been up for ");
    kputd((system_ticks / (CYCLES_PER_TICK))); 
    kputs(" seconds.");
}

void do_ps(int argc, char **argv)
{
    kputs("PID   STATE            SP_ADDR");

    for (long i = 0; i < MAX_TASKS; i++)
    {
        kputd(task_table[i].id); 
        kprint("     "); 
  
        switch (task_table[i].state)
        {
        case 0:
            kprint("TASK FREE");
            break;
        case 1:
            kprint("TASK READY");
            break;
        case 2:
            kprint("TASK RUNNING");
            break;
        case 3:
            kprint("TASK SLEEPING");
            break;
        default:
            break;
        }

        kprint("      0x"); 
        kputh(task_table[i].sp_address); 
        kputs("");
    }
}