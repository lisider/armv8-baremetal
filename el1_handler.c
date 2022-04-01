/*************************************************************************
  > File Name: el1_handler.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Thu 31 Mar 2022 10:36:11 PM CST
 ************************************************************************/
#include "stdio.h"

void svc_handler(int num){
    printf("svc handler\n");
    return ;
}
