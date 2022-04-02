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

char *strcpy(char *dest, const char *src){
    char *ret = dest;
    while( (*dest++ = *src++) != '\0' );
    return ret;
}

u64 strtoul(char *s)
{
    int ret;
    int radix = 10;
    int negative = 0;
    int i;
    ret = 0;
    if(NULL==s)return ret;
    if(*s == '-') {
        negative = 1;
        s++;
    }
    else if(*s == '0') {
        s++;
        if((*s == 'x')||(*s == 'X')){
            s++;
            radix = 0x10;
        }
    }
    else if((*s == 'H')||(*s=='h')) {
        s++;
        radix = 0x10;
    }
    while (*s) {
        if (*s >= '0' && *s <= '9')
            i = *s - '0';
        else if (*s >= 'a' && *s <= 'f')
            i = *s - 'a' + 0xa;
        else if (*s >= 'A' && *s <= 'F')
            i = *s - 'A' + 0xa;
        else
            break;
        if(i >= radix) break;
        ret = (ret * radix) + i;
        s++;

    }
    return negative?(-ret):ret;
}
