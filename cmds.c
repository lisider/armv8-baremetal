/*************************************************************************
  > File Name: cmds.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 04:35:11 PM CST
 ************************************************************************/
#include "stdio.h"
#include "string.h"
#include "cmd.h"

CMD(help){

    struct cmd *p = NULL;
    char * tmp = NULL;
    int count = 0;

    p = &__initcall_start;
    do {
        printf("%2d : %s\n",count+1,p->name);
        tmp = (char *)p;
        tmp +=32;
        p= (struct cmd *)tmp;
        count ++;
    } while (p < &__initcall_end);

    if(p >= &__initcall_end)
        printf("total : %d\n",count);
}



CMD(ct){

    struct cmd *p = NULL;
    char * tmp = NULL;
    int count = 0;

    p = &__initcall_start;
    do {
        tmp = (char *)p;
        tmp +=32;
        p= (struct cmd *)tmp;
        count ++;
    } while (p < &__initcall_end);

    if(p >= &__initcall_end)
        printf("%d\n",count);
}




CMD(quit){
    printf("%s\n",__func__);
}


CMD(brk){
    printf("%s enter\n",__func__);
    asm("BRK #0X0");
    printf("%s exit\n",__func__);
}

CMD(svc){
    printf("%s enter\n",__func__);
    asm("LDR X8,=0x1");
    asm("SVC #0x0");
    printf("%s exit\n",__func__);
}

#include "cc.h"
CMD(cc){

    if (argc != 2){
        printf("Usage for calling_convention :\n");
        printf("\tcc c_call_asm\n");
        printf("\tcc c_call_c\n");
        printf("\tcc asm_call_c\n");
        printf("\tcc c_embedded_assembly\n");
        return ;
    }
    if (strcmp((char *)argv + 32,"c_call_asm") == 0){
        cc_asm_argc_0_return_0();
        cc_asm_argc_1_return_0(0x12345678);
        cc_asm_argc_2_return_0(0x12345678,0x55555555);
        cc_asm_argc_0_return_1();
    }else if (strcmp((char *)argv + 32,"c_call_c") == 0){
        cc_c_argc_0_return_0();
        cc_c_argc_1_return_0(0x12345678);
        cc_c_argc_2_return_0(0x12345678,0x55555555);
        cc_c_argc_0_return_1();
    }else if (strcmp((char *)argv + 32,"asm_call_c") == 0){
        cc_asm_caller_argc_0();
        cc_asm_caller_argc_1();
        cc_asm_caller_argc_2();
    }else if (strcmp((char *)argv + 32,"c_embedded_assembly") == 0){
        printf("0X%08X\n",cc_c_embedded_assembly());
    }
}

#include "a64_exercises.h"
CMD(a64){

    if (argc != 2){
        printf("Usage for a64 exercises :\n");
        printf("\ta64 dp_fc : data_processing_and_flow_control\n");
        printf("\ta64 am    : accessing memory\n");
        printf("\ta64 sc    : system control\n");
        return ;
    }
    if (strcmp((char *)argv + 32,"dp_fc") == 0){
        int ret;
        ret = gcd(0x40,0x30);
        printf("ret:0X%08X\n",ret);
        ret = gcd(0x30,0x40);
        printf("ret:0X%08X\n",ret);
        ret = gcd(0x40,0x40);
        printf("ret:0X%08X\n",ret);
    }else if (strcmp((char *)argv + 32,"am") == 0){
        unsigned char *src    = "hello world";
        unsigned char dst[32] = {0};
        my_memcpy(src,dst,11);
        printf("%s\n",dst);
    }else if (strcmp((char *)argv + 32,"sc") == 0){
        printf("SP       :0X%016lx\n",get_sp());
    }
}



//-------------------------------------------------------------

CMD(new){
    printf("%s\n",__func__);
    int i = 0;
    for(; i<argc; i++){
        printf("Argument %d is %s\n", i, (char *)argv + i*32);
    }
}
