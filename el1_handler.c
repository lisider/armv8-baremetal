/*************************************************************************
  > File Name: el1_handler.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Thu 31 Mar 2022 10:36:11 PM CST
 ************************************************************************/
#include "stdio.h"
#include "shell.h"


void brk_handler(){
    shell_debug();
}

void svc_handler(){
    printf("%s\n",__func__);
}

void el021_sync_handler(int num){
    printf("%s\n",__func__);
    int EC = (num&0xfc000000)>>26;
    int IL = (num&0x02000000)>>25;
    int ISS= (num&0x01ffffff);

    printf("EC :%08X,IL :%08X,ISS :%08X\n",EC,IL,ISS);

    switch(EC){
        case 0X15:{
                      svc_handler();
                      break;
                  }
        case 0x3C:{
                      brk_handler();
                      asm("stp x0,x1,[sp , #-16]!");
                      asm("MRS X0,ELR_EL1");
                      asm("ADD X0,X0,4");
                      asm("MSR ELR_EL1,X0");
                      asm("ldp x0,x1,[sp], #16");
                      break;
                  }
    }

    return ;
}
