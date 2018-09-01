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
#include "myUART.h"
#include "myADC.h"

void main(void)
{
    unsigned int adcValue;

    mcuInit();
    uartInit(0);
    adcInit();

    printf("rotation sensor program start\r\n");

    while (1)
    {
        delay_ms(500);

        // PORTF.0
        adcValue = read_adc(0x00);

        printf("adc value : %d\r\n", adcValue);
    }
}
