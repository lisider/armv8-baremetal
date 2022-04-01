/*************************************************************************
  > File Name: parse.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 04:33:50 PM CST
 ************************************************************************/
#include "stdio.h"
#include "string.h"
#include "cmd.h"


void not_find(){
    printf("command not found\n");
}


fun_t parse(const char * name){

    struct cmd *p = NULL;
    char * tmp = NULL;

    p = &__initcall_start;
    do {
        if(strcmp(p->name,name) == 0){
            return p->fun;
        }else{
            tmp = (char *)p;
            tmp +=32;
            p= (struct cmd *)tmp;
        }
    } while (p < &__initcall_end);

    if(p >= &__initcall_end)
        return not_find;

}


