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

extern char sp,ev[][3],ev_i,main_f,time[9],clock_reg[3];
static unsigned int key_timer = 0;
static unsigned char pre_key=0xff,flag=0,key,f;  
void settime(char key_2)
{
    static unsigned char i=7,HR=0,MN=0,SEC=0;
    static unsigned int l;
    if(!f)
    {
      f = 1;
      if (clock_reg[0] & 0x40)
      {
          HR =  ((clock_reg[0] >> 4) & 0x01);
		  HR =  (clock_reg[0] & 0x0F);
      }
      else
      {
          HR =  ((clock_reg[0] >> 4) & 0x03);
		  HR =  (clock_reg[0] & 0x0F);
      }
      MN =  ((clock_reg[1] >> 4) & 0x0F);
	  MN =  (clock_reg[1] & 0x0F);
      SEC = ((clock_reg[2] >> 4) & 0x0F);
	  SEC =  (clock_reg[2] & 0x0F);
    }
    clcd_print("HH:MM:SS        ",LINE1(0));    
    if(l++ <= 200)
    {
        clcd_putch(' ', LINE2(i-1));
        clcd_putch(' ', LINE2(i));
    }
    else if(l <= 400)
    {
        
        clcd_putch('0' + HR/10,LINE2(0));
        clcd_putch('0' + HR%10,LINE2(1));
        clcd_putch(':' , LINE2(2));
        clcd_putch('0' + MN/10,LINE2(3));
        clcd_putch('0' + MN%10,LINE2(4));
        clcd_putch(':' , LINE2(5));
        clcd_putch('0' + SEC/10,LINE2(6));
        clcd_putch('0' + SEC%10,LINE2(7));
    }   
    else if (l > 400)
    {
        l = 0;
    }
    if (key_2 == ALL_RELEASED)
        flag = 1; 
    
    if(flag==1)
    {
        pre_key = key;
        key = read_switches(LEVEL_CHANGE); 
    }   
    
    if(key == MK_SW11 && key_timer<=1500 || key == MK_SW12 && key_timer<=1500)  
    {
        key_timer++;
    }
    
    else if((pre_key == MK_SW11) && key_timer <= 1500)
    {
        l=0;
        key_timer = 0;
        if(i == 1)
        {
            HR++;
            if(HR>23)
                HR=0;
        }
        if(i == 4)
        {
            MN++;
            if(MN>59)
                MN=0;
        }
        if(i == 7)
        {
            SEC++;
            if(SEC>59)
                SEC=0;           
        }    
    }
    else if((pre_key == MK_SW12) && key_timer <=1500)
    {
        key_timer = 0;
     
        if(i==7)
            i = 4;
        else if(i == 4)
            i = 1;
        else if(i == 1)
            i = 7;        
    }
    
    else if((pre_key == MK_SW11) && key_timer > 1500)
    {
        key_timer = 0;
        HR = ((HR / 10 << 4) | (HR % 10));
        MN = ((MN / 10 << 4) | (MN % 10));
        SEC = ((SEC  / 10 << 4) | (SEC % 10));
        write_ds1307(HOUR_ADDR,HR);                               
        write_ds1307(MIN_ADDR,MN);
        write_ds1307(SEC_ADDR,SEC);
        ev_i = 10;
        f=0;
        store_event();
        CLEAR_DISP_SCREEN;
        main_f = MENU;
    }
    
    else if((pre_key == MK_SW12) && key_timer > 1500)
    {
        key_timer = 0;
        CLEAR_DISP_SCREEN;
        main_f = MENU;
    }   
    
}