#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "timer.h"
#include "eeprom.h"
#include "ext_eeprom.h"
extern char time[9], ev[][3], ev_i, sp,lap,o_f;
extern char main_f;
static unsigned char key,count = 1;
static unsigned char pre_key;  
static unsigned int key_timer = 0;  

void view_log(char key_2)
{
    static char current_lap=0,flag=0;
    if(flag == 0)
        if(o_f==1) 
            current_lap = lap+1;
        else
            current_lap = 0;
    
    char data[10];    
    clcd_print("logs", LINE1(0));
    
    clcd_putch(count/10 + 48, LINE2(0));
    clcd_putch(count%10 + 48, LINE2(1));
    
    
    for (char i = 0; i < 10; i++)
    {
        data[i] = read_ext_eeprom(((current_lap%10)*10)+i);
    }      
    clcd_putch(data[0], LINE2(2));  
    clcd_putch(data[1], LINE2(3));  
    clcd_putch(':', LINE2(4));     
    clcd_putch(data[2], LINE2(5));  
    clcd_putch(data[3], LINE2(6));  
    clcd_putch(':', LINE2(7));      
    clcd_putch(data[4], LINE2(8));  
    clcd_putch(data[5], LINE2(9));  
    clcd_putch(' ', LINE2(10));     
    clcd_putch(data[6], LINE2(11)); 
    clcd_putch(data[7], LINE2(12)); 
    clcd_putch(' ', LINE2(13));     
    clcd_putch(data[8], LINE2(14)); 
    clcd_putch(data[9], LINE2(15));     
    
    if (key_2 == ALL_RELEASED)
    {
        flag = 1;
    }    
    if(flag==1)
    {
        pre_key = key;
        key = read_switches(LEVEL_CHANGE); 
        flag = 1;
    }
    if(key == MK_SW11 && key_timer<=1500 || key == MK_SW12 && key_timer<=1500)  
    {
        key_timer++;
    }
    else if(key == MK_SW12 && key_timer>=1500)  
    {
        main_f = MENU;
        flag = 0;
        key_timer=0;
        pre_key = 0xFF;
        CLEAR_DISP_SCREEN;
    }
    else if(key_timer>0 && key_timer<1500) 
    {
        if(pre_key == MK_SW11)
        {
            if (count > 1) 
            {
                count--;
                current_lap--;
            }
        }
        else if(pre_key == MK_SW12)
        {
            if ((o_f == 1 && count < 10) || (o_f != 1 && count < lap)) 
            {
                count++;
                current_lap++;
            }
        }
        key_timer = 0;
    }
}