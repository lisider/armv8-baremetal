/*************************************************************************
  > File Name: cmd.h
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 04:35:46 PM CST
 ************************************************************************/
#ifndef __CMD_H__
#define __CMD_H__

extern struct cmd __initcall_start, __initcall_end;
extern struct cmd __initcall_debug_start, __initcall_debug_end;

typedef void(*fun_t)(int argc, char** argv);

struct cmd{
    char name[16];
    fun_t fun;
};

#define TO_STRING(name) #name
#define FUN_NAME(name) name##_fun
#define DEBUG_FUN_NAME(name) name##_debug_fun

#define CMD(name) \
    static void FUN_NAME(name)(int argc, char** argv);\
    static struct cmd name __attribute__((section("data_ptrs"))) __attribute__((aligned(32))) = {\
        TO_STRING(name),\
        FUN_NAME(name),\
    };\
   static void FUN_NAME(name)(int argc, char** argv)

#define DCMD(name) \
    static void DEBUG_FUN_NAME(name)(int argc, char** argv);\
    static struct cmd name __attribute__((section("debug_ptrs"))) __attribute__((aligned(32))) = {\
        TO_STRING(name),\
        DEBUG_FUN_NAME(name),\
    };\
   static void DEBUG_FUN_NAME(name)(int argc, char** argv)


#endif
