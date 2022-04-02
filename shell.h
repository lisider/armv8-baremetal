#ifndef __SHELL_H__
#define __SHELL_H__
#include <stdint.h>

#define CNTLQ       0x11
#define CNTLS       0x13
#define DEL         0x7F
#define BACKSPACE   0x08
#define TAB         0x09
#define LF          0x0A
#define CR          0x0D
#define ESC         0x1B

#ifndef FALSE
/* FALSE macro */
#define FALSE (0==1)
#endif
#ifndef TRUE
/* TRUE macro */
#define TRUE (!(FALSE))
#endif

#define CMDLINE_BUF		256
extern char oldcmd[CMDLINE_BUF];

extern int getline (char *lp, uint32_t n, uint8_t dsp);
extern long int mystrtoul(char *s);
extern char * utoa(char *s, unsigned int u);
extern char * get_entry (char *cp, char **pNext);
extern void shell_user(void);
extern void shell_debug(void);

#endif // __SHELL_H__
