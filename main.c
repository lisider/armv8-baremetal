#include "uart.h"
#include "stdio.h"
#include "types.h"
#include "shell.h"

void main(void) 
{
    printf("Hello World\n");
    asm("LDR X8,=0x1");
    asm("SVC #0x0");

    shell();
    return;
}
