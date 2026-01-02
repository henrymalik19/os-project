.section .text
.globl _start

_start:
    la sp, _STACK_TOP
    call kernel_main

spin:
    j spin
    