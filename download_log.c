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
#include "ext_eeprom.h"

extern char time[9],ev[][3],ev_i,sp,lap,o_f;
extern char main_f;
void download_log()
{
    static int l=0;
    static char lap1,flag1=0;
    char data[10];
    if(l++<=500)
    {
        clcd_print("Download log    ",LINE1(0));
        clcd_print("Success         ",LINE2(0));
    }
    else{
    if(o_f==1)
        lap1 = 10;
    else
        lap1 = lap;
   
    for(int i=0;i<lap1;i++)
    {
        for(int j=0;j<10;j++)
        {
            data[j]=read_ext_eeprom(i*10+j);     
        }
        putch(data[0]);
        putch(data[1]);
        putch(':');
        putch(data[2]);
        putch(data[3]);
        putch(':');
        putch(data[4]);
        putch(data[5]);
        putch(' ');
        putch(data[6]);
        putch(data[7]);
        putch(' ');
        putch(data[8]);
        putch(data[9]);
        puts("\n\r");
    }
    
    ev_i = 8;
    store_event();
    l=0;
    CLEAR_DISP_SCREEN;
    main_f = MENU;
    }
    
}