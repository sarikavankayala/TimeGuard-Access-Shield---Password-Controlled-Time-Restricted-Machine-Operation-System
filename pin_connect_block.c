#include<LPC21xx.h>
void cfgportpinFunc(unsigned int portNo,unsigned int pinNo,unsigned int pinFunc)
{
if(portNo==0)
{
if(pinNo<16)
{
PINSEL0=((PINSEL0&(3<<(pinNo*2)))|(pinFunc<<(pinNo*2)));
}
else if(pinNo>=16&&pinNo<=31)
{
PINSEL1=((PINSEL1&~(3<<((pinNo-16)*2)))|(pinFunc<<((pinNo-16)*2)));
}
}
else if(portNo==1)
{
}
}
