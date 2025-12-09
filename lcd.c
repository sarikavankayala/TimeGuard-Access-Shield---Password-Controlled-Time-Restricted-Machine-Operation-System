#include "types.h"
#include "arduino_defines.h"
#include "arduino.h"
#include "lcd_defines.h"
#include "delay.h"
void WriteLCD(u8 byte)
{
	digitalWrite(LCD_RW,0);
	write2pins(LCD_DATA,8,byte);
	digitalWrite(LCD_EN,1);
	delay_us(1);
	digitalWrite(LCD_EN,0);
	delay_ms(2);
}
void CmdLCD(u8 Cmdbyte)
{
	digitalWrite(LCD_RS,0);
	WriteLCD(Cmdbyte);
}
void Init_LCD(void)
{
	portMode(LCD_DATA,11,OUTPUT);
	delay_ms(15);
	CmdLCD(MODE_8BIT_1LINE);
	delay_us(100);
	CmdLCD(MODE_8BIT_1LINE);
	delay_us(100);
	CmdLCD(MODE_8BIT_1LINE);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DISP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}
void CharLCD(u8 asciiVal)
{
	digitalWrite(LCD_RS,1);
	WriteLCD(asciiVal);
}
void StrLCD(s8 *p)
{
	while(*p)
		CharLCD(*p++);
}
void U32LCD(u32 n)
{
	u8 digit[10];
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n>0)
		{
			digit[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(digit[i]);
		}
	}
}
void S32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
	U32LCD(n);
}
void F32LCD(f32 fn,u32 nDP)
{
	u32 i,n;
	if(fn<0.0)
	{
		CharLCD('-');
		fn=-fn;
	}
	n=fn;
	U32LCD(n);
	CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		fn=(fn-n)*10;
		n=fn;
		CharLCD(n+48);
	}
}
void BuildCGRAM(u8 *p,u8 nByte)
{
	u32 i;
	CmdLCD(GOTO_CGRAM_START);
	digitalWrite(LCD_RS,1);
	for(i=0;i<nByte;i++)
	{
		WriteLCD(p[i]);
	}
	CmdLCD(GOTO_LINE1_POS0);
}
