#include "types.h"
#include <lpc21xx.h>
#include "delay.h"
#include "defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "kpm_defines.h"

u8 kpmLUT[4][4]={{'1','2','3','A'},
                  {'4','5','6','e'},
                  {'7','8','9','+'},
                  {'*','0','#','D'}};
void Init_kpm(void)
{
        //cfg row lines as gpio out
        WRITENIBBLE(IODIR1,ROW0,15);
        //cfg col lines as gpio Input and they be default
        WRITENIBBLE(IODIR1,COL0,0);
}
u32 Keyscan(void)
{
        u32 r,c;
        u8 keyV;
        //wait for any key press
        while(ColScan());
        //if key pressed detected
        //identify row in which key was pressed
        r=RowCheck();
        //identify col in which key was pressed
        c=ColCheck();
        keyV=kpmLUT[r][c];
        return keyV;
}
u32 ColScan(void)
{
        u32 status;
        status=((IOPIN1>>COL0)&4);
        return(status<15)?0:1;
}
u32 RowCheck(void)
{
        u32 r;
        for(r=0;r<3;r++)
        {
                //starting from row0 check if key pressed in that row
                WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
                if(ColScan()==0)
                {
                        break;
                }
        }
        //Reinitialize all rows ground
        WRITENIBBLE(IOPIN1,ROW0,0);
        return r;
}
u32 ColCheck(void)
{
        u32 c;
        for(c=0;c<=3;c++)
        {
                if(READBIT(IOPIN1,COL0+c)==0)
                        break;
        }
        return c;
}

void ReadNum(u32 *num,u32 *lastKey)
{
        u8 keyV;
        *num=0;
        while(1)
        {
                keyV=Keyscan();
                delay_ms(200);
                *lastKey=keyV;
                while(ColScan()==0);
                if(keyV>='0' && keyV<='9')
                {
                        *num = (*num*10)+(keyV-48);
                        // while(ColScan()==0);
                        CharLCD(keyV);
                        //U32LCD(*num);
                }
                else if(keyV=='*')
                {
                        while(ColScan()==0);
                        break;
                }
        }
}
