
#include <mega128.h>
#include <string.h>

#include "myUART.h"

/*
    PORTE.0 : RXD0
    PORTE.1 : TXD0

    PORTD.2 : RXD1
    PORTD.3 : TXD1
*/

// Bit definitions from the USART control registers
#ifndef RXB8
#define RXB8 1
#endif

#ifndef TXB8
#define TXB8 0
#endif

#ifndef UPE
#define UPE 2
#endif

#ifndef DOR
#define DOR 3
#endif

#ifndef FE
#define FE 4
#endif

#ifndef UDRE
#define UDRE 5
#endif

#ifndef RXC
#define RXC 7
#endif

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// Define the new putchar function
void putchar(char c)
{
    while ((UCSR0A & DATA_REGISTER_EMPTY)==0);
    UDR0=c;
}

// USART1 Receiver buffer
#define RX_BUFFER_SIZE1 64

char rx_buffer1[RX_BUFFER_SIZE1];

#if RX_BUFFER_SIZE1 <= 256
unsigned char rx_wr_index1,rx_rd_index1,rx_counter1;
#else
unsigned int rx_wr_index1,rx_rd_index1,rx_counter1;
#endif

// This flag is set on USART1 Receiver buffer overflow
bit rx_buffer_overflow1;

// USART1 Receiver interrupt service routine
interrupt [USART1_RXC] void usart1_rx_isr(void)
{
    char status,data;

    status=UCSR1A;
    data=UDR1;

    if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0)
    {
       rx_buffer1[rx_wr_index1++]=data;
#if RX_BUFFER_SIZE1 == 256
       // special case for receiver buffer size=256
       if (++rx_counter1 == 0) rx_buffer_overflow1=1;
#else
       if (rx_wr_index1 == RX_BUFFER_SIZE1) rx_wr_index1=0;
       if (++rx_counter1 == RX_BUFFER_SIZE1)
          {
          rx_counter1=0;
          rx_buffer_overflow1=1;
          }
#endif
    }
}

// Get a character from the USART1 Receiver buffer
#pragma used+
char getchar1(void)
{
    char data;

    while (rx_counter1==0);

    data=rx_buffer1[rx_rd_index1++];

#if RX_BUFFER_SIZE1 != 256
    if (rx_rd_index1 == RX_BUFFER_SIZE1)
        rx_rd_index1=0;
#endif

#asm("cli")
    --rx_counter1;
#asm("sei")

    return data;
}
#pragma used-

// Write a character to the USART1 Transmitter
#pragma used+
void putchar1(char c)
{
    while ((UCSR1A & DATA_REGISTER_EMPTY)==0);
    UDR1=c;
}
#pragma used-

void uartInit(unsigned char line)
{
    switch(line)
    {
        case 0:
            // Communication Parameters: 8 Data, 1 Stop, No Parity
            // USART0 Receiver: Off
            // USART0 Transmitter: On
            // USART0 Mode: Asynchronous
            // USART0 Baud Rate: 9600
            UCSR0A=0x00;
            UCSR0B=0x08;
            UCSR0C=0x06;
            UBRR0H=0x00;
            UBRR0L=0x67;
            break;
        case 1:
            // Communication Parameters: 8 Data, 1 Stop, No Parity
            // USART1 Receiver: On
            // USART1 Transmitter: On
            // USART1 Mode: Asynchronous
            // USART1 Baud Rate: 9600
            UCSR1A=0x00;
            UCSR1B=0x18;
            UCSR1C=0x06;
            UBRR1H=0x00;
            UBRR1L=0x67;
            break;
        default:
            break;
    }
}

