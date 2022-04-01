/*************************************************************************
  > File Name: dcmds.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 04:35:11 PM CST
 ************************************************************************/
#include "stdio.h"
#include "cmd.h"
#include "dlib.h"

DCMD(help){

    struct cmd *p = NULL;
    char * tmp = NULL;
    int count = 0;

    p = &__initcall_debug_start;
    do {
        printf("%2d : %s\n",count+1,p->name);
        tmp = (char *)p;
        tmp +=32;
        p= (struct cmd *)tmp;
        count ++;
    } while (p < &__initcall_debug_end);

    if(p >= &__initcall_debug_end)
        printf("total : %d\n",count);
}



DCMD(ct){

    struct cmd *p = NULL;
    char * tmp = NULL;
    int count = 0;

    p = &__initcall_debug_start;
    do {
        tmp = (char *)p;
        tmp +=32;
        p= (struct cmd *)tmp;
        count ++;
    } while (p < &__initcall_debug_end);

    if(p >= &__initcall_debug_end)
        printf("%d\n",count);
}

DCMD(quit){
}


DCMD(regs){
    printf("EL0 regs before \"BRK\" instruction :\n");
    show_regs(pt_regs);
}

//-------------------------------------------------------------

DCMD(new){
    printf("%s\n",__func__);
}
