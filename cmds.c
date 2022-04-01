/*************************************************************************
  > File Name: cmds.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 04:35:11 PM CST
 ************************************************************************/
#include "stdio.h"
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



//-------------------------------------------------------------


CMD(new){
    printf("%s\n",__func__);
}
