/*************************************************************************
  > File Name: string.c
  > Author: SuWeishuai
  > Mail: suwsl@foxmail.com
  > Created Time: Fri 01 Apr 2022 03:02:53 PM CST
 ************************************************************************/

#include "string.h"
int strcmp(const char *s1, const char *s2)
{
    while(*s1 && (*s1==*s2)){
        ++s1;
        ++s2;
    }
    return *s1 - *s2;
}
