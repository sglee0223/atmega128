
#include <mega128.h>

#include "mySPI.h"

void spiRead(unsigned char *pdata, unsigned char len)
{
    unsigned char i;

    for (i=0; i<len; i++)
    {
        //SPDR = 0x00; // no dummy
        while(!(SPSR & (1 << SPIF)));
        pdata[i] = SPDR;
    }
}

void spiWrite(unsigned char *pdata, unsigned char len)
{
    unsigned char i;

    for (i=0; i<len; i++)
    {
        SPDR = pdata[i];
        while(!(SPSR & (1 << SPIF)));
        //byte = SPDR; // no dummy
    }
}

void spiInit(void)
{
    SPI_DDR |= ((1 << SS) | (1 << SCK) | (1 << MOSI));

    SPI_PORT |= (1 << SS);

    SPCR = ((1 << SPE)|(1 << MSTR)|(1 << SPR0)); // 16M/16=1Mhz
}

