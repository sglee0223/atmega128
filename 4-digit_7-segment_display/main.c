/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2018-09-01
Author  : Windows »ç¿ëÀÚ
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*****************************************************/

#include <mega128.h>
#include <delay.h>

#include "myMCU.h"

// Declare your global variables here

void main(void)
{
/*
    PORTA 
    7bit ~ 0bit
    d1 / A / B / C / D / E / F / G
                
     _      a
    | |   f   b
     -      g 
    | |   e   c   
     -      d    d1
    
    0    0x3f    0011 1111  
    1    0x06    0000 0110
    2    0x5B    0101 1011
    3    0x4f    0100 1111
    4    0x66    0110 0110
    5    0x6d    0110 1101
    6    0x7d    0111 1101
    7    0x27    0010 0111
    8    0x7f    0111 1111
    9    0x67    0110 0111  
    
    PORTC ( 4 digit on/off, low show, high hide )
    3bit ~ 0bit
    D4 / D3 / D2 / D1

    0111 7     
    1011 b
    1101 d
    1110 e
*/

    unsigned char i=0;
    
    unsigned char digit[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
    unsigned char dot[] = {0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00};
    unsigned char show[] = {0x07, 0x0b, 0x0d, 0x0e, 0x0d, 0x0b, 0x07, 0x0b, 0x0d, 0x0e};

    mcuInit();
              
    //fndInit();
    
    PORTA = 0x00;
    DDRA  = 0xff;
        
    PORTC = 0x00;
    DDRC  = 0x0f; 

    while (1)
    {              
        //fndShow();
        
        PORTA = digit[i] | dot[i];
        PORTC = show[i];
        i++;
        if (i >= 10) i = 0;
        
        delay_ms(1000);
    }
}
