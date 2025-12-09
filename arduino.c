#include "arduino_defines.h"
#include "types.h" 
#include <LPC21xx.h>
void pinMode(u32 pinNo,u32 pindir)
{
	 if(pinNo<32)
	 {
		 if(pindir==OUTPUT)
		 {
			  IODIR0 |=1<<pinNo;
		 }
		 else
		 {
			 IODIR0 &=~(1<<pinNo);
		 }
	 }
	 else if(pinNo>=32&&pinNo<=47)
	 {
		 if(pindir==OUTPUT)
		 {
			 IODIR1|=1<<(pinNo-16);
		 }
		 else
		 {
			  IODIR1&=~(1<<(pinNo-16));
		 }
	 }
}
void digitalWrite(u32 pinNo,u32 bit)
{
	 if(pinNo<32)
	 {
		 bit?(IOSET0=1<<pinNo):(IOCLR0=1<<pinNo);
	 }
	 else if(pinNo>=32&&pinNo<=47)
	 {
		 bit?(IOSET1=1<<(pinNo-16)):(IOCLR1=1<<(pinNo-16));
	 }
}
u32 digitalRead(u32 pinNo)
{
	u32 bit;
	if(pinNo<32)
	{
		bit=((IOPIN0>>pinNo)&1);
	}
	else if(pinNo>=32&&pinNo<=47)
	{
		bit=((IOPIN1>>(pinNo-16))&1);
	}
	return bit;
}
void portMode(u32 pinstartNo,u32 npins,u32 pindir)
{
	 if(pinstartNo<32)
	 {
		 if(pindir==OUTPUT)
		 {
			  IODIR0 |=((1<<npins)-1)<<pinstartNo;
		 }
		 else
		 {
			 IODIR0 &=~((1<<npins)-1)<<pinstartNo;
		 }
	 }
	 else if(pinstartNo>=32&&pinstartNo<=47)
	 {
		 if(pindir==OUTPUT)
		 {
			 IODIR1|=((1<<npins)-1)<<(pinstartNo-16);
		 }
		 else
		 {
			  IODIR1&=~((1<<npins)-1)<<(pinstartNo-16);
		 }
	 }
}
void write2pins(u32 pinstartNo,u32 npins,u32 bit)
{
	 if(pinstartNo<32)
	 {
		 IOPIN0=((IOPIN0&~(((1<<npins)-1)<<pinstartNo))|(bit<<pinstartNo));
	 }
	 else if(pinstartNo>=32&&pinstartNo<=47)
	 {
		 IOPIN1=((IOPIN1&~(((1<<npins)-1)<<(pinstartNo-16)))|(bit<<(pinstartNo-16)));
	 }
}
u32 read2pins(u32 pinstartNo,u32 npins)
{
	u32 bit;
	if(pinstartNo<32)
	{
		bit=((IOPIN0>>pinstartNo)&((1<<npins)-1));
	}
	else if(pinstartNo>=32&&pinstartNo<=47)
	{
		bit=((IOPIN1>>(pinstartNo-16))&((1<<npins)-1));
	}
	return bit;
}

