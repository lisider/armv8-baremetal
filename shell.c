#include "shell.h"
#include "stdio.h"
#include "uart.h"
#include "parse.h"
#include "string.h"

char *PROMPT ="suws@baremetel:~$ ";
char *PROMPT_DEBUG ="suws@debug:~$ ";
char *intro=
"********************\n"
"****LITTLE SHELL****\n"
"********************\n"
;

char *intro_debug=
"********************\n"
"*MONITOR DEBUG SHELL\n"
"********************\n"
;


char oldcmd[CMDLINE_BUF];
int getline(char *lp, uint32_t n, uint8_t dsp)
{
    uint32_t cnt = 0;
    int c;
    c = -1;
    do {
        c = getchar();
        switch (c) {
            case CNTLQ:                       /* ignore Control S/Q             */
            case CNTLS:
                break;;
            case BACKSPACE:
            case DEL:
                if (cnt == 0) {
                    break;
                }
                cnt--;                         /* decrement count                */
                lp--;                          /* and line pointer               */
                putchar(0x08);                /* echo backspace                 */
                putchar(' ');
                putchar(0x08);
                break;
            case ESC:
                *lp = 0;                       /* ESC - stop editing line        */
                return (FALSE);
            case TAB:
                for(c=0;(oldcmd[c]!=CR)&&(oldcmd[c]!=LF)&&(oldcmd[c]!=0)&&(cnt<60);c++){
                    *lp = oldcmd[c];
                    lp++;
                    cnt++;
                    if(dsp)putchar(oldcmd[c]);
                    else putchar('*');
                }
                break;
            case CR:                          /* CR - done, stop editing line   */
                *lp = c;
                lp++;                          /* increment line pointer         */
                cnt++;                         /* and count                      */
                c = LF;
            default:
                *lp = c;
                if(dsp)putchar(c);             /* echo and store character       */
                else putchar('*');
                lp++;                          /* increment line pointer         */
                cnt++;                         /* and count                      */
                break;
        }
    } while (cnt < n - 2  &&  c != LF);     /* check limit and CR             */
    *lp = 0;                                /* mark end of string             */
    for(c=0;c<=cnt;c++)
        oldcmd[c]= *(lp-cnt+c);
    return (TRUE);
}

long int mystrtoul(char *s)
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

char* utoa(char *s, unsigned int u)
{
    char temp[10]={0};
    uint8_t i=0;
    if(NULL==s) return NULL;
    if(0==u){
        *s = '0';
        s++;
        *s = 0;
        return s;
    }
    while(0!=u){
        temp[i++]='0'+u%10;
        u /= 10;
    }
    while(i>0){
        *s=temp[--i];
        s++;
    }
    *s = 0;
    return s;
}


char *get_entry (char *cp, char **pNext) {
    char *sp, lfn = 0, sep_ch = ' ';
    if (cp == NULL) {                          /* skip NULL pointers          */
        *pNext = cp;
        return (cp);
    }
    for ( ; *cp == ' ' || *cp == '\"'; cp++) { /* skip blanks and starting  " */
        if (*cp == '\"') { sep_ch = '\"'; lfn = 1; }
        *cp = 0;
    }
    for (sp = cp; *sp != CR && *sp != LF; sp++) {
        if ( lfn && *sp == '\"') break;
        if (!lfn && *sp == ' ' ) break;
    }
    for ( ; *sp == sep_ch || *sp == CR || *sp == LF; sp++) {
        *sp = 0;
        if ( lfn && *sp == sep_ch) { sp ++; break; }
    }
    *pNext = (*sp) ? sp : NULL;                /* next entry                  */
    return (cp);
}


void shell_user(void)
{
    char *sp,*next,*before;
    int argc = 0;
    char argv[4][32]={"0"};
    printf (intro);
    while (TRUE) {
        argc = 0;
        printf (PROMPT);
        if (getline(oldcmd, sizeof (oldcmd), 1) == FALSE) {
            continue;
        }

        before = &oldcmd[0];
        sp = get_entry (before, &next);
        if (*sp == 0) { // enter only
            continue;
        }
        strcpy(argv[0],sp);
        argc ++;

        while(next){    // have parameter
            before = next;
            sp = get_entry (before, &next);
            strcpy(argv[argc],sp);
            argc ++;
        }

        parse(argv[0])(argc,(char **)argv);

    }
    return ;
}

void shell_debug(void)
{
    char *sp,*next,*before;
    int argc = 0;
    char argv[4][32]={"0"};
    printf (intro_debug);
    while (TRUE) {
        argc = 0;
        printf (PROMPT_DEBUG);
        if (getline(oldcmd, sizeof (oldcmd), 1) == FALSE) {
            continue;
        }

        before = &oldcmd[0];
        sp = get_entry (before, &next);
        if (*sp == 0) { // enter only
            continue;
        }

        if (strcmp(sp,"quit") == 0)
            break;

        strcpy(argv[0],sp);
        argc ++;

        while(next){    // have parameter
            before = next;
            sp = get_entry (before, &next);
            strcpy(argv[argc],sp);
            argc ++;
        }

        parse_debug(argv[0])(argc,(char **)argv);

    }
    return ;
}
