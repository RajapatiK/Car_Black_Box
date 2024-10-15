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


char main_f = 0, menu_f = 0,key,sp,ev[][3]={"ON","GR","GN","G1","G2","G3","G4"," C","DL","CL","ST","CP"},ev_i;
inti_config()
{
    PEIE = 1;
    GIE = 1;
    init_clcd();
    init_adc();
    init_matrix_keypad();
    init_timer0();
    init_i2c();
	init_ds1307();
    init_uart();
}

void main(void) 
{
    inti_config(); 
    get_time();
    sp = read_adc(4)/10.33;
    store_event();
    write_ext_eeprom(200,8);
    while (1)
    {        
        sp = read_adc(CHANNEL4)/10.33;
        key = read_switches(STATE_CHANGE);
        if(key == MK_SW2)
        {
            if(ev_i < 6)
                ev_i++;
            else if(ev_i == 7)
                ev_i = 2;
            store_event();
        }
        else if(key == MK_SW3)
        {
            if(ev_i == 7)
                ev_i = 2;
            else if(ev_i > 1)
                ev_i--;
            store_event();
        }
        else if(key == MK_SW1)
        {
            ev_i = 7;
            store_event();
        }
        if(main_f == DASHBOARD)
        {
            dashboard();
             if(key == MK_SW11)
            {
                CLEAR_DISP_SCREEN;
                main_f = PASSWORD;
            }
        }
        else if(main_f == PASSWORD)
        {
            password(key);
        }
        else if(main_f == MENU)
        {
            menu(key);
        }
        else if(main_f == MENU_ENTER)
        {
            if(menu_f == VIEWLOG)
            {
                view_log(key);
            }
            else if(menu_f == DOWNLOADLOG)
            {
                download_log();
            }
            else if(menu_f == CLEARLOG)
            {
               clear_log(key);
            }
            else if(menu_f == SETTIME)
            {
                settime(key);
            }
            else if(menu_f == CHANGEPASS)
            {
               change_pass(key);
            }
       }
    }      
    
}
