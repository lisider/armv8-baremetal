#include "uart.h"

volatile unsigned int * const UART0DR = (unsigned int *)0x09000000;
volatile unsigned int * const UART0FR = (unsigned int *)0x09000018;
 
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


uint16_t getchar(void){
    while ((*UART0FR & 0x00000010) != 0);
    uint16_t ch = *UART0DR;
    return (0xFF & ch);
}

int putchar(int ch){
    *UART0DR = ch;
    return 0;
}
