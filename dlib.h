/*************************************************************************
  > File Name: dlib.h
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Sat 02 Apr 2022 12:56:27 AM CST
 ************************************************************************/
#ifndef DLIB_H
#define DLIB_H
#include "types.h"

struct pt_regs {  // size:272
    u64 regs[31];
    u64 sp;
    u64 pc;
    u64 pstate;
};

extern struct pt_regs * pt_regs;

void show_regs(struct pt_regs * pt_regs);


#endif
