#include "uart.h"
#include "stdio.h"
#include "types.h"
#include "shell.h"

void main(void) 
{
    printf("hello\n");
    printf("%s\n","hello");
    printf("%08X\n",0x01);
    print_uart0("Hello World\n");

    asm("LDR X8,=0x1");
    asm("SVC #0x0");
    print_uart0("Hello World2\n");

    shell();
    return;
}
