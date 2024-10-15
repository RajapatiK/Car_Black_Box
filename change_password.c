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

extern char main_f,time[9],ev[][3],ev_i,sp,lap;
static char new_pass = 0,re_pass;


void change_pass(char key)
{
    int p=0;
    static char j = 0;
    static char i = 0;
    static char k = 0;
    static int l = 0;  
    static int M = 0; 
    static int o = 0; 
   
    if(k == 0)
    {
        clcd_print("Enter New Pswd", LINE1(0)); 
        if(i <= 3)
        {
            if(l++ == 500)
            {
                clcd_putch('_', LINE2(i));
            }
            else if(l == 1000)
            {
                l = 0;
                clcd_putch(' ', LINE2(i));
            }
        }
        if((key == MK_SW11) && i <= 3)
        {
            if(i < 3)
            {
                new_pass = (new_pass << 1); 
                clcd_putch('*', LINE2(i));
            }
            else
            {
                clcd_putch('*', LINE2(i));
            }
            i++;
        }
        else if(key == MK_SW12 && i <= 3)
        {
            if(i < 3)
            {
                new_pass = (new_pass | 1) << 1;
                clcd_putch('*', LINE2(i));
            }
            else
            {
                clcd_putch('*', LINE2(i));
            }
            i++;
        }
        else if(i==4)
        {
            k=1;
            CLEAR_DISP_SCREEN;
        }
    }
    if(k == 1)
    {
        clcd_print("ReEnter New Pswd", LINE1(0));
        if(j <= 3)
        {
            if(M++ == 500)
            {
                clcd_putch('_', LINE2(j));
            }
            else if(M == 1000)
            {
                M = 0;
                clcd_putch(' ', LINE2(j));
            }
        }
        if((key == MK_SW11) && j <= 3)
        {
            if(j < 3)
            {
                re_pass = (re_pass << 1);
                clcd_putch('*', LINE2(j));
            }
            else
                clcd_putch('*', LINE2(j));
            j++;
        }
        else if(key == MK_SW12 && j <= 3)
        {
            if(j < 3)
            {
                re_pass = (re_pass | 1) << 1;  
                clcd_putch('*', LINE2(j));
            }
            else
            {
                clcd_putch('*', LINE2(j));
            }
            j++;
        }
        else if(j==4)
        {
            k=2;
            CLEAR_DISP_SCREEN;
        }
    }
    if(j==4 && i==4)
    {
        if(new_pass == re_pass )
        {          
            o = 0;
            j = 0;
            i = 0;
            k = 0;
            write_ext_eeprom(200,new_pass);
            new_pass = 0;
            re_pass = 0;
            ev_i = 11;
            store_event();
            CLEAR_DISP_SCREEN;
            main_f =  MENU; 
        }
        else
        {
            if(o++ < 1000 && o > 0)
            {
                clcd_print("Not matching    ", LINE2(0));
            }
            if(o > 1000 && o < 2000)
            {
                k = 2;
                clcd_print("Try Again        ", LINE1(0));
            }
            if(o == 2000)
            {
                o = 0;
                j = 0;
                i = 0;
                k = 0;
                new_pass = 0;
                re_pass = 0;
                CLEAR_DISP_SCREEN;
            }
        }
    }
}
