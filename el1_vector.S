.section ".text.vector_el1", "ax"

.balign 0x800 // because the low [10:0] of the VBAR_EL1 is Reserved
              // The .balign directive provides the same alignment
              // functionality as .align with a consistent behavior
              // across all architectures
// vector table for EL1
.global vec_tbl_el1
vec_tbl_el1:
curr_el_sp0_sync:
    WFI

.balign 0x80
curr_el_sp0_irq:
    WFI

.balign 0x80
curr_el_sp0_fiq:
    WFI

.balign 0x80
curr_el_sp0_serr:
    WFI

.balign 0x80
curr_el_spx_sync:
    MRS X1, ESR_EL1
    WFI

.balign 0x80
curr_el_spx_irq:
    WFI

.balign 0x80
curr_el_spx_fiq:
    WFI

.balign 0x80
curr_el_spx_serr:
    WFI


.balign 0x80
lower_el_64b_sync: // svc from el0 & el1 is 64bit
    // caculator sp
    sub sp,sp,272  //   16 * 17
    // save user pt_regs
    stp x0,  x1,  [sp, #16 * 0]
    stp	x2,  x3,  [sp, #16 * 1]
    stp	x4,  x5,  [sp, #16 * 2]
    stp	x6,  x7,  [sp, #16 * 3]
    stp	x8,  x9,  [sp, #16 * 4]
    stp	x10, x11, [sp, #16 * 5]
    stp	x12, x13, [sp, #16 * 6]
    stp	x14, x15, [sp, #16 * 7]
    stp	x16, x17, [sp, #16 * 8]
    stp	x18, x19, [sp, #16 * 9]
    stp	x20, x21, [sp, #16 * 10]
    stp	x22, x23, [sp, #16 * 11]
    stp	x24, x25, [sp, #16 * 12]
    stp	x26, x27, [sp, #16 * 13]
    stp	x28, x29, [sp, #16 * 14]
    mrs	x21, sp_el0
    // we save sp_el0 & elr_el1 & spsr_el1
    // just for read
    stp	x30, x21, [sp, #16 * 15] // sp_el0
    mrs	x22, elr_el1
    mrs	x23, spsr_el1
    stp	x22, x23, [sp, #16 * 16] // elr_el1 & spsr_el1

    mov x0,sp
    bl el021_sync_handler

    ldp	x0,  x1,  [sp, #16 * 0]
    ldp	x2,  x3,  [sp, #16 * 1]
    ldp	x4,  x5,  [sp, #16 * 2]
    ldp	x6,  x7,  [sp, #16 * 3]
    ldp	x8,  x9,  [sp, #16 * 4]
    ldp	x10, x11, [sp, #16 * 5]
    ldp	x12, x13, [sp, #16 * 6]
    ldp	x14, x15, [sp, #16 * 7]
    ldp	x16, x17, [sp, #16 * 8]
    ldp	x18, x19, [sp, #16 * 9]
    ldp	x20, x21, [sp, #16 * 10]
    ldp	x22, x23, [sp, #16 * 11]
    ldp	x24, x25, [sp, #16 * 12]
    ldp	x26, x27, [sp, #16 * 13]
    ldp	x28, x29, [sp, #16 * 14]
    ldr	x30, [sp, #16 * 15]
    // we didn't crack sp_el0 & elr_el1 & spsr_el1
    // so we need not to restore
    ERET

.balign 0x80
lower_el_64b_irq:
    WFI

.balign 0x80
lower_el_64b_fiq:
    WFI

.balign 0x80
lower_el_64b_serr:
    WFI

.balign 0x80
lower_el_32b_sync:
    WFI

.balign 0x80
lower_el_32b_irq:
    WFI

.balign 0x80
lower_el_32b_fiq:
    WFI

.balign 0x80
lower_el_32b_serr:
    WFI
