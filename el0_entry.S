.section ".text.el0", "ax"
.balign 4
.global _el0_entry
_el0_entry:

    ldr x30, =stack_top	// setup stack
    mov sp, x30
    bl main

    ADR X1, _el0_entry
    LDR X2, =(16 * (1 << 20))
    ADD X2, X1, X2
    AND SP, X2, #(~0b1111)
    SVC #0x0
