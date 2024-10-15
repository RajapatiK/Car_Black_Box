#include <xc.h>
#include "main.h"

extern char main_f,w_count,cnt,del_sec;

void __interrupt() isr(void)
{
	static unsigned int count;
    static unsigned int count1;    
    
    if (TMR0IF)
    {
        TMR0 = TMR0 + 8;
        if (count++ == 20000)
        {
            count=0;
            w_count--;           
        }
        else if(w_count==0)
        {
            cnt=2;
            w_count=120;        
        }
        TMR0IF = 0;	
    }
    
}