/*************************************************************************
  > File Name: cc.S
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Mon 04 Apr 2022 06:18:07 PM CST
 ************************************************************************/

.section ".text.el0", "ax"
.balign 4
.global cc_asm_argc_0_return_0
cc_asm_argc_0_return_0:
	nop
	ret

.global cc_asm_argc_1_return_0
cc_asm_argc_1_return_0:
	sub	sp, sp, #0x10
	str	w0, [sp, #12]
	nop
	add	sp, sp, #0x10
	ret

.global cc_asm_argc_2_return_0
cc_asm_argc_2_return_0:
	sub	sp, sp, #0x10
	str	w0, [sp, #12]
	str	w1, [sp, #8]
	nop
	add	sp, sp, #0x10
	ret

.global cc_asm_argc_0_return_1
cc_asm_argc_0_return_1:
	mov	w0, #0x5678                	// #22136
	movk	w0, #0x1234, lsl #16
	ret

.global cc_asm_caller_argc_0
cc_asm_caller_argc_0:
    stp	x29, x30, [sp, #-16]!
    mov	x29, sp
    bl cc_c_argc_0_return_0
    nop
    ldp	x29, x30, [sp], #16
    ret

.global cc_asm_caller_argc_1
cc_asm_caller_argc_1:
    stp	x29, x30, [sp, #-32]!
    mov	x29, sp
    mov x0, #0x1234
    bl cc_c_argc_1_return_0
    nop
    ldp	x29, x30, [sp], #32
    ret

.global cc_asm_caller_argc_2
cc_asm_caller_argc_2:
    stp	x29, x30, [sp, #-32]!
    mov	x29, sp
    mov x0, #0x1234
    mov x1, #0x5678
    bl cc_c_argc_2_return_0
    nop
    ldp	x29, x30, [sp], #32
    ret

