#ifndef __MYSPI_H
#define __MYSPI_H

#define SPI_DDR     DDRB
#define SPI_PORT    PORTB
#define SS          PORTB0
#define SCK         PORTB1
#define MOSI        PORTB2
#define MISO        PORTB3

void spiRead(unsigned char *pdata, unsigned char len);
void spiWrite(unsigned char *pdata, unsigned char len);
void spiInit(void);

#endif
