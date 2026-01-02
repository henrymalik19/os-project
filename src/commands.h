#ifndef COMMANDS_H
#define COMMANDS_H

struct command
{
    char *name;
    char *description;
    void (*handler)(int argc, char **argv);
};

extern struct command cmd_table[];

void do_help(int argc, char **argv);
void do_echo(int argc, char **argv);
void do_hang(int argc, char **argv);
void do_info(int argc, char **argv);
void do_uptime(int argc, char **argv);
void do_ps(int argc, char **argv);

#endif
