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
