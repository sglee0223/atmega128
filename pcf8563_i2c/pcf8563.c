
#include <mega128.h>

#include <stdio.h>
#include <string.h>
#include <delay.h>

#include "myI2C.h"
#include "pcf8563.h"

void I2C_Scan(void)
{
    unsigned int i = 0;

	printf("Scanning I2C bus...\r\n");

	for(i = 0; i < 128; i++)
	{                
		if(getI2C(i<<1, REG_YEAR))   
		{
			unsigned char msg[64]={0,};

			snprintf(msg, sizeof(msg), "0x%02X", i);
			printf("%s", msg);
		}
        else
		{
			printf(".");
		}
        delay_ms(10);
	}

	printf("\r\n");
}

void setI2C(unsigned char rtc_addr, unsigned char reg, unsigned char data)
{
    unsigned char ret = 0;
	unsigned char tx_buffer[2] = {0,};

	tx_buffer[0] = reg;
	tx_buffer[1] = data;		
    ret = WriteData(rtc_addr, tx_buffer, sizeof(tx_buffer));
		
	if (ret == 0)
	{
		//printf("setI2C: Not Okay[0x%x]\r\n", reg);
	}		
}

unsigned char getI2C(unsigned char rtc_addr, unsigned char reg)
{
    unsigned char ret = 0;
    unsigned char rx_buffer[1] = {0,};
    
    ret = ReadData(rtc_addr, reg, rx_buffer);
	if (ret == 0)
	{
		//printf("getI2C: Not Okay[0x%x][ret:0x%x]\r\n", reg, ret);
	}	
    
    return rx_buffer[0];
}

void RTC_Init(unsigned char rtc_addr)
{
    setI2C(rtc_addr, REG_CTRL_STATUS_1, 0x00);
    setI2C(rtc_addr, REG_CTRL_STATUS_2, 0x00);
}

void PCF8563_setDate(unsigned char rtc_addr, unsigned short year, unsigned char mon, unsigned char day)
{
    year	= changeIntToHex(year % 100);
    mon 	= changeIntToHex(mon) | ((year > 1999) ? 0x00 : 0x80);
    day 	= changeIntToHex(day);
		
    setI2C(rtc_addr, REG_YEAR, year);
    setI2C(rtc_addr, REG_MON, mon);
    setI2C(rtc_addr, REG_DAY, day);
}

void PCF8563_getDate(unsigned char rtc_addr)
{
    unsigned char buf[3];
    unsigned char century = 0;
    unsigned short year;
    unsigned char mon, day;
	
    buf[0] = getI2C(rtc_addr, REG_YEAR);
    buf[1] = getI2C(rtc_addr, REG_MON);
    buf[2] = getI2C(rtc_addr, REG_DAY);

    if (buf[1] & 0x80)
        century = 1;
		
    buf[0] = buf[0]&0xff;
    buf[1] = buf[1]&0x1f;
    buf[2] = buf[2]&0x3f;
		
    year = (century == 1) ? (1900 + changeHexToInt(buf[0])) : (2000 + changeHexToInt(buf[0]));
    mon = changeHexToInt(buf[1]);
    day = changeHexToInt(buf[2]);

    printf("%d-%d-%d ", year, mon, day);
}

void PCF8563_setTime(unsigned char rtc_addr, unsigned char hour, unsigned char min, unsigned char sec)
{
    setI2C(rtc_addr, REG_HOUR, changeIntToHex(hour));
    setI2C(rtc_addr, REG_MIN, changeIntToHex(min));
    setI2C(rtc_addr, REG_SEC, changeIntToHex(sec));
}

void PCF8563_getTime(unsigned char rtc_addr)
{
    unsigned char hour, min, sec;

    hour = changeHexToInt(getI2C(rtc_addr, REG_HOUR) & 0x3f);
    min  = changeHexToInt(getI2C(rtc_addr, REG_MIN) & 0x7f);
    sec  = changeHexToInt(getI2C(rtc_addr, REG_SEC) & 0x7f);

    printf("%d:%d:%d\r\n", hour, min, sec);
}
