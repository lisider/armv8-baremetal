#include "uart.h"

void main(void) 
{
    print_uart0("Hello World\n");

    asm("LDR X8,=0x1");
    asm("SVC #0x0");
    print_uart0("Hello World2\n");
    return;
}
