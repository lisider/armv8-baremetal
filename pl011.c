#include "uart.h"

volatile unsigned int * const UART0DR = (unsigned int *)0x09000000;
 
void print_uart0(const char *s) 
{
    while(*s != '\0') { 		        /* Loop until end of string */
         *UART0DR = (unsigned int)(*s); /* Transmit char */
          s++;			                /* Next char */
    }
}

void uart_write(const void *buf, size_t count){
    size_t i = 0;
    for (;i<count;i++){
         *UART0DR = (unsigned int)*((unsigned char*)buf+i); /* Transmit char */
    }
}
