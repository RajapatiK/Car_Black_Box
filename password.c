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

unsigned char cnt = 2;
unsigned char w_count;
char d_count=0;
char out_pass = 0;  
char in_pass;
extern char main_f;
char  g = 1;


void password(char key)
{   
    static int j = 0;
    static char i = 0;
    static char k = 0;
    static int l = 0;     
                  
    if(k == 0)
        clcd_print("Enter Password", LINE1(0));

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
            out_pass = (out_pass << 1);  
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
            out_pass = (out_pass | 1) << 1;  
            clcd_putch('*', LINE2(i));
        }
        else
        {
            out_pass = (out_pass | 1);  
            clcd_putch('*', LINE2(i));
        }
        i++;
    }

    if(i == 4)
    {
        in_pass = read_ext_eeprom(200);
        if(out_pass == in_pass)
        {
            j = 0;
            i = 0;
            k = 0;
            out_pass = 0;
            cnt = 2;
            CLEAR_DISP_SCREEN;
            main_f =  MENU;            
        }
        else
        {
            if(cnt)
            {
                if(j++ < 1000 && j > 0)
                {
                    clcd_print("failure             ", LINE2(0));
                }
                if(j > 1000 && j < 2000)
                {
                    k = 1;
                    clcd_print("Try Again        ", LINE1(0));
                    clcd_putch('0' + cnt, LINE2(0));
                    clcd_print(" Attempt Left    ", LINE2(1));
                }
                if(j == 2000)
                {
                    clcd_print("                ", LINE2(0)); 
                    j = 0;
                    i = 0;
                    k = 0;
                    cnt--;
                    out_pass = 0; 
                }
            }
            else if(cnt == 0)
            {
                k = 1;
                if (g == 1) 
                    w_count = 120;
                g=0;
                clcd_print("You are blocked ", LINE1(0));
                clcd_print("for ", LINE2(0));                
                clcd_putch('0'+(w_count/100), LINE2(5));
                clcd_putch('0'+(w_count/10)%10, LINE2(6));
                clcd_putch('0'+ w_count%10, LINE2(7));
                clcd_print(" seconds", LINE2(8));
                if(w_count==0)
                {
                    out_pass = 0;  
                    j = 0;
                    i = 0;
                    k = 0;
                }
            }
        }
    }
}
