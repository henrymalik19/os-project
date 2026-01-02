ENTRY(_start)

SECTIONS
{
  _RAM_START = 0x80000000;
  _KERNEL_BASE = _RAM_START + 0x200000;
  . = _KERNEL_BASE;
  
  _TEXT_START = .;
  .text : {
    *(.text .text.*)
  }  
  _TEXT_END = .;

  . = ALIGN(4);

  _RODATA_START = .;
  .rodata : {
    *(.rodata .rodata.*)
  }
  _RODATA_END = .;

  . = ALIGN(4);

  _DATA_START = .;
  .data : {
    *(.data .data.*)
  }
  _DATA_END = .;

  . = ALIGN(4);

  _BSS_START = .;
  .bss : {
    *(.bss .bss.*)
    *(COMMON)

    . = ALIGN(16);
    _STACK_BOTTOM = .;
    . = . + 4096;     /* allocate 4 KiB stack */
    _STACK_TOP = .;
  }
  _BSS_END = .;

  _KERNEL_END = .;

  . = ALIGN(4096);
  _HEAP_START = .;

  _RAM_END = _RAM_START + ((1024 * 1024) * 128);
}
