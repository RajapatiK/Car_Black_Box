#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "timer.h"


extern char main_f,menu_f;
static unsigned char key;
void menu(char key_2)
{
    char name[][16]={"VIEWLOG       ","DOWNLOADLOG   ","CLEARLOG      ","SETTIME       ","CHANGEPASS    "};
    static char flag=0,view=0,star=0;
    static int val=0,val2=0;

    if(key_2 == ALL_RELEASED)
    {
        flag=1;
    }
    if(flag==1)
    {
    key = read_switches(LEVEL_CHANGE);
    if(star == 0)
    {
         clcd_putch('*',LINE1(0));
         clcd_putch(' ',LINE2(0));
    }
     if(star == 1)
    {
         clcd_putch(' ',LINE1(0));
         clcd_putch('*',LINE2(0));
    }
    clcd_print(name[view],LINE1(2));
    clcd_print(name[view+1],LINE2(2));
    
    if(key == MK_SW12)
    {
        val++;
        if(val>1500)
        {
            val=0;
            main_f = DASHBOARD;
            CLEAR_DISP_SCREEN;          
        }
    }
    else if(val<=1500 && val!=0)
    {
        val=0;
        if(star == 0)
            star=1;
        else
        {
            if(view<3)
            {
                view++;
            }
        }
    }
    if(key == MK_SW11)
    {
        val2++;
        if(val2>1500)
        {
            val2=0;
            main_f = MENU_ENTER;
            CLEAR_DISP_SCREEN;
            menu_f = star+view; 
        }
    }
    else if(val2<=1500 && val2!=0)
    {
        val2=0;
        if(star == 1)
            star=0;
        else
        {
            if(view>0)
            {
                view--;
            }
        }
    }
    }
}
