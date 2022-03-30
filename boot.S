.section ".text.boot", "ax"
.balign 4
.global _start
_start:
    // We will default reset to EL1, because Qemu default not support EL2/3
    // Initialize VBAR_EL1
    LDR X1, =vec_tbl_el1
    MSR VBAR_EL1, X1
    // Enable async exception
    // If an interrupt is not routed to EL3 or EL2,
    // it is routed to EL1 by default.
    // When a target Exception level is higher than the current Exception level
    // and the target Exception level is EL1, the asynchronous exception is
    // masked if PSTATE.{A,I,F} is 1. So we only need to set DAIF registers
    MSR DAIFClr, #0x7

    // We ignore initializing general purpose registers
    // Initialize the SP_EL1
    LDR X1, =el1_stack_top
    MOV SP, X1

    // Initialize system control registers
    // SA, SA0, CP15BEN, EOS, nTWI, nTWE, EIS, SPAN, nTLSMD, LSMAOE bits is set
    LDR X1, =0x30C50838
    MSR SCTLR_EL1, x1

    // Enable FP registers accessing from EL1 and EL0
    MOV X1, #(0x3 << 20)
    MSR CPACR_EL1, X1
    
    // Prepare entring EL0
    MOV X0, #0b00000
    MSR SPSR_EL1, X0
    LDR X0, =_el0_entry
    MSR ELR_EL1, X0
    ERET

.balign 0x800
// vector table for EL1
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
lower_el_64b_sync:
    WFI

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
