MEMORY
{
    FLASH (rx)  : ORIGIN = 0x8000000, LENGTH = 16M
    RAM (xrw)   : ORIGIN = 0x20000000, LENGTH = 8M
}


ENTRY(_init)

STACK_SIZE = 32K;

SECTIONS
{
    . = 0x80000000;

    .text : {
        build/rv/init.o(.text)
        *(.text)
    } > FLASH

    .data : {
        *(.data)
    } >RAM AT> FLASH

    .sdata : {
        *(.sdata)
    } >RAM

    .bss : {
        __bss_start = .;
        PROVIDE(__global_pointer$ = . + 2K);
        *(.bss)
        *(.sbss)
        _end = .;
        __heap_start = .;
    } > RAM

    .stack (NOLOAD) : {
        . = ALIGN(16);
        __stack_start = ORIGIN(RAM) + LENGTH(RAM) - STACK_SIZE - 16;
        . = . + STACK_SIZE;
        __stack_end = ORIGIN(RAM) + LENGTH(RAM) - 16;
        __heap_end = __stack_start;
    } > RAM
}
