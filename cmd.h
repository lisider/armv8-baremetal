/*************************************************************************
  > File Name: cmd.h
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 04:35:46 PM CST
 ************************************************************************/
#ifndef __CMD_H__
#define __CMD_H__

extern struct cmd __initcall_start, __initcall_end;

typedef void(*fun_t)(void);

struct cmd{
    char name[16];
    fun_t fun;
};

#define TO_STRING(name) #name
#define FUN_NAME(name) name##_fun

#define CMD(name) \
    static void FUN_NAME(name)(void);\
    static struct cmd name __attribute__((section("data_ptrs"))) __attribute__((aligned(32))) = {\
        TO_STRING(name),\
        FUN_NAME(name),\
    };\
   static void FUN_NAME(name)(void)

#endif
