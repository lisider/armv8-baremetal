/*************************************************************************
  > File Name: dcmds.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 04:35:11 PM CST
 ************************************************************************/
#include "stdio.h"
#include "cmd.h"
#include "dlib.h"
#include "string.h"
#include "sreg_ops.h"
#include "mem_ops.h"

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

DCMD(reg){

    if (argc == 1){
        printf("Usage : reg MPIDR_EL1 CurrentEL\n");
        return ;
    }
    int i = 1;
    for(; i<argc; i++){
        if (strcmp((char *)argv + i*32,"MPIDR_EL1") == 0){
            printf("MPIDR_EL1: 0x%lx\n", mrs(MPIDR_EL1));
        }else if (strcmp((char *)argv + i*32,"CurrentEL") == 0){
            u64 lvl = mrs(CurrentEL);
            printf("CurrentEL: 0x%lx | EL%d\n", lvl,(lvl >> 2) & 0x3);
        }
    }
}

DCMD(wr){

    if (argc != 3){
        printf("Usage : wr 0x40080000 0x12345678\n");
        return ;
    }
    u64 addr  = strtoul((char *)argv + 1*32);
    u64 data  = strtoul((char *)argv + 2*32);
    write64(addr,data);
}

DCMD(rd){

    if (argc != 2){
        printf("Usage : rd 0x40080000\n");
        return ;
    }
    u64 addr  = strtoul((char *)argv + 1*32);
    printf("0x%lx\n",read64(addr) );
}

#include "a64_exercises.h"
DCMD(a64){

    if (argc != 2){
        printf("Usage for a64 exercises :\n");
        printf("\ta64 sc    : system control\n");
        return ;
    }
    if (strcmp((char *)argv + 32,"sc") == 0){
        printf("SP       :0X%016lx\n",get_sp());
        printf("CurrentEL:0X%016lx\n",get_currentEL());
    }
}

//-------------------------------------------------------------

DCMD(new){
    printf("%s\n",__func__);
    int i = 0;
    for(; i<argc; i++){
        printf("Argument %d is %s\n", i, (char *)argv + i*32);
    }
}
