#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "eeprom.h"
#include "matrix_keypad.h"
#include "timer.h"
#include "i2c.h"
#include "ds1307.h"
#include "uart.h"

extern char lap,o_f, main_f,time[9],ev[][3],ev_i,sp;
void clear_log(char key)
{
    static int l=0;
    if(l++<500)
    {
        clcd_print("Clear Log       ", LINE1(0));
        clcd_print("Success         ", LINE2(0));
    }
    else
    {
        l=0;
        lap = 0;
        o_f = 0;
        ev_i = 9;
        store_event();
        CLEAR_DISP_SCREEN;
        main_f = MENU;
    }
}