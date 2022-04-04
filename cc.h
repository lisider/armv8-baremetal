/*************************************************************************
  > File Name: cc.h
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Mon 04 Apr 2022 06:15:35 PM CST
 ************************************************************************/

#ifndef CC_H
#define CC_H

void cc_c_argc_0_return_0(void);
void cc_c_argc_1_return_0(int a);
void cc_c_argc_2_return_0(int a,int b);
int  cc_c_argc_0_return_1(void);

void cc_asm_argc_0_return_0(void);
void cc_asm_argc_1_return_0(int a);
void cc_asm_argc_2_return_0(int a,int b);
int  cc_asm_argc_0_return_1(void);

void cc_asm_caller_argc_0(void);
void cc_asm_caller_argc_1(void);
void cc_asm_caller_argc_2(void);

int  cc_c_embedded_assembly(void);

#endif
