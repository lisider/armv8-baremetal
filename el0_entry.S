.section ".text.el0", "ax"
.balign 4
.global _el0_entry
_el0_entry:
    // 在不同的特权级下，通用寄存器 sp(即栈寄存器) 会引用 sp_el0 或 sp_el1
    // （即 sp 相当于 sp_el0 或 sp_el1 的别名
    ldr x30, =el0_stack_top	// setup stack for SP_EL0
    mov sp, x30
    bl main

loop:
    mov x0,x0
    mov x1,x1
    mov x2,x2
    b loop


