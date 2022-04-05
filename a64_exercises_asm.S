/*************************************************************************
  > File Name: a64_exercises_asm.S
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Tue 05 Apr 2022 08:08:46 PM CST
 ************************************************************************/

.section ".text.el0", "ax"
.balign 4
.global gcd
gcd:
    CMP w0, w1 // Compare a and b
    B.EQ gcd_end // If they are equal, skip to the end
    B.LS less_than // If unsigned less than, branch to b = b -a
    SUB w0, w0, w1 // a = a - b
    B gcd // Branch back to start
less_than:
    SUB w1, w1, w0 // b = b - a
    B gcd // Branch back to start
gcd_end:
    RET

.global my_memcpy
my_memcpy:
    CBZ w2, my_memcpy_end // Check for number of bytes being 0
    LDRB w3, [x0], #1 // Load byte[n] from src, post-incrementing pointer
    STRB w3, [x1], #1 // Store byte[n] to dst, post-incrementing pointer
    SUBS w2, w2, #1 // Decrement number of bytes, updating ALU flags
    B.NE my_memcpy // Branch if number of bytes remaining not 0
my_memcpy_end:
    RET

.global get_sp
get_sp:
    MOV X0,SP
    RET

.global get_currentEL
get_currentEL:
    MRS X1,CurrentEL
    MOV X2,#0x2
    LSR X0,X1,X2
    RET
