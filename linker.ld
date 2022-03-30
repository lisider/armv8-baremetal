SECTIONS
{
    . = 0x40080000;
    .text : { *(.text.boot) }
    .data : { *(.data) }
    .bss : { *(.bss COMMON) }
    . = 0x40880000;
    el1_stack_top = .;
    . = 0x40a80000;
    .text.el0 : { *(.text) }
	. = ALIGN(8);
	. = . + 0x1000; /* 4kB of stack memory */
	el0_stack_top = .;
}
