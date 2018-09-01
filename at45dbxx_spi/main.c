/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Automatic Program Generator
© Copyright 1998-2011 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 2018-08-31
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

#include "myMCU.h"
#include "myUART.h"
#include "mySPI.h"

#include "at45dbxx.h"

void main(void)
{
    mcuInit();
    uartInit(0);
    spiInit();

    printf("at45dbxx program start\r\n");

    at45db_initialize();
    at45db_test();

    while (1)
    {

    }
}
