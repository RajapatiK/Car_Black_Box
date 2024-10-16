#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "i2c.h"
#include "ds1307.h"
#include "ext_eeprom.h"

unsigned char time[9],clock_reg[3];
extern char sp,ev[][3],ev_i;
void dashboard()
{
    get_time();
    clcd_print("TIME      EV  SP",LINE1(0));
    clcd_print(time,LINE2(0));
    clcd_putch(sp/10+48,LINE2(14));
    clcd_putch(sp%10+48,LINE2(15));
    clcd_print(ev[ev_i],LINE2(10));
}
void get_time()
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}


