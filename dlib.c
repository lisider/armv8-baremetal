/*************************************************************************
  > File Name: dlib.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Sat 02 Apr 2022 12:56:09 AM CST
 ************************************************************************/

#include "dlib.h"
#include "stdio.h"

struct pt_regs * pt_regs = NULL;


void show_regs(struct pt_regs * pt_regs)
{
    printf("  x0-x3: %016lx %016lx %016lx %016lx\n", pt_regs->regs[0], pt_regs->regs[1], pt_regs->regs[2], pt_regs->regs[3]);
    printf("  x4-x7: %016lx %016lx %016lx %016lx\n", pt_regs->regs[4], pt_regs->regs[5], pt_regs->regs[6], pt_regs->regs[7]);
    printf(" x8-x11: %016lx %016lx %016lx %016lx\n", pt_regs->regs[8], pt_regs->regs[9], pt_regs->regs[10], pt_regs->regs[11]);
    printf("x12-x15: %016lx %016lx %016lx %016lx\n", pt_regs->regs[12], pt_regs->regs[13], pt_regs->regs[14], pt_regs->regs[15]);
    printf("x16-x19: %016lx %016lx %016lx %016lx\n", pt_regs->regs[16], pt_regs->regs[17], pt_regs->regs[18], pt_regs->regs[19]);
    printf("x20-x23: %016lx %016lx %016lx %016lx\n", pt_regs->regs[20], pt_regs->regs[21], pt_regs->regs[22], pt_regs->regs[23]);
    printf("x24-x27: %016lx %016lx %016lx %016lx\n", pt_regs->regs[24], pt_regs->regs[25], pt_regs->regs[26], pt_regs->regs[27]);
    printf("x28-x30: %016lx %016lx %016lx\n", pt_regs->regs[28], pt_regs->regs[29], pt_regs->regs[30]);
    printf("     sp: %016lx\n", pt_regs->sp);
    printf("     pc: %016lx\n", pt_regs->pc);
    printf(" pstate: %016lx\n", pt_regs->pstate);
}


