#ifndef __PCF8563_H
#define __PCF8563_H

#define RTC_ADDR (0x51 << 1)

#define REG_CTRL_STATUS_1		0x00
#define REG_CTRL_STATUS_2		0x01

#define REG_SEC		0x02
#define REG_MIN		0x03
#define REG_HOUR  0x04

#define REG_DAY		0x05
#define REG_WEEK	0x06
#define REG_MON		0x07
#define REG_YEAR	0x08

#define REG_MIN_ALARM		0x09
#define REG_HOUR_ALARM	0x0A
#define REG_DAY_ALARM		0x0B
#define REG_WEEK_ALARM	0x0C

#define REG_CLKOUT_CTRL			0x0D
#define REG_TIMER_CTRL			0x0E
#define REG_TIMER_COUNT_VAL	0x0F

#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define changeHexToInt(hex)		( ( ((hex)>>4) *10 ) + ((hex)%16) )

void I2C_Scan(void);
void setI2C(unsigned char rtc_addr, unsigned char reg, unsigned char data);
unsigned char getI2C(unsigned char rtc_addr, unsigned char reg);
void RTC_Init(unsigned char rtc_addr);
void PCF8563_setDate(unsigned char rtc_addr, unsigned short year, unsigned char mon, unsigned char day);
void PCF8563_getDate(unsigned char rtc_addr);
void PCF8563_setTime(unsigned char rtc_addr, unsigned char hour, unsigned char min, unsigned char sec);
void PCF8563_getTime(unsigned char rtc_addr);

#endif
