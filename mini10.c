// Paste your corrected full C code here.
// Please provide your original full file so I can insert the corrected version.
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "delay.h"
#include "eint.h"
#include "pin_connect_block.h"
#include "pin_function_defines.h"
#include "types.h"
#include <string.h>
#include <stdlib.h>
#include "kpm.h"
#include "kpm_defines.h"
#include <LPC21xx.h>

#define ENT_SW 3
#define LED_PIN 5

u32 S_TIME=2,E_TIME=3;

s32 date,month,year,day,hour,minute,second;
u32 key,flag,num,lastkey,i,b;

s8 ORG_P[]="12345";
s8 CNT_P[10];
s8 TMP_P[10];

void open_edit_menu(void);
void readpassword(u32 *,u32*);
void readtime(u32 *time,u32 *lastkey);
void changetime(void);
void changemachinetime(void);
void changepassword(void);
void changedate(void);
void changeday(void);
int password(void);

void open_edit_menu()
{
        while(1)
  {
     i:CmdLCD(CLEAR_LCD);
	   CmdLCD(GOTO_LINE1_POS0);
                 StrLCD("1:CHNG PSWD");
                 CmdLCD(GOTO_LINE1_POS0+11);
                 StrLCD("2:TIME");
     CmdLCD(GOTO_LINE2_POS0);
                 StrLCD("3:EDT_M_TIME");
                 CmdLCD(GOTO_LINE2_POS0+11);
                 StrLCD("4:EXIT");
     key=Keyscan();
     if(key=='1')
     {
                         CmdLCD(CLEAR_LCD);
                         StrLCD("Password change");
                         CmdLCD(GOTO_LINE2_POS0);
                         StrLCD("welcome");
       delay_s(1);
                         changepassword();
                 }
     else if(key=='2')
     {
                         CmdLCD(CLEAR_LCD);
                         CmdLCD(GOTO_LINE1_POS0);
                         StrLCD("1:time");
                         CmdLCD(GOTO_LINE1_POS0+10);
                         StrLCD("2:date");
                         CmdLCD(GOTO_LINE2_POS0);
                         StrLCD("3:day");
                         CmdLCD(GOTO_LINE2_POS0+10);
                         StrLCD("4:exit");
                         delay_s(1);
                         key=Keyscan();
                         if(key=='1')
       {
          CmdLCD(CLEAR_LCD);
                            CmdLCD(GOTO_LINE1_POS0);
          StrLCD("--WELCOME--");
          CmdLCD(GOTO_LINE2_POS0);
          StrLCD("Change time");
          delay_s(1);
		   changetime();
       }
       else if(key=='2')
       {
          CmdLCD(CLEAR_LCD);
                            CmdLCD(GOTO_LINE1_POS0);
          StrLCD("--WELCOME--");
          CmdLCD(GOTO_LINE2_POS0);
          StrLCD("Change date");
          delay_s(1);
          changedate();
       }
       else if(key=='3')
       {
          CmdLCD(CLEAR_LCD);
                            CmdLCD(GOTO_LINE1_POS0);
          StrLCD("--WELCOME--");
          CmdLCD(GOTO_LINE2_POS0);
          StrLCD("Change day");
          delay_s(1);
          changeday();
       }
       else if(key=='4')
       {
           goto i;
                         }
                 }
     else if(key=='3')
     {
                         CmdLCD(CLEAR_LCD);
                         CmdLCD(GOTO_LINE1_POS0);
                         StrLCD("--WELCOME--");
                         CmdLCD(GOTO_LINE2_POS0);
                         StrLCD("MAC_TIME_CHANGE");
                         delay_s(1);
                         changemachinetime();
                 }
     else if(key=='4')
                 {
                         break;
						  }
}
}

void changeday()
{
     do{
        CmdLCD(CLEAR_LCD);
        StrLCD("0:S 1:M 2:T 3:W");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("4:T 5:F 6:S");
        delay_ms(200);
        key=Keyscan();
        while(ColScan()==0);
        day=key-'0';
    }while(day<0 || day>6);
    SetRTCDay(day);
    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
    CmdLCD(GOTO_LINE1_POS0+2);
    StrLCD("DAY UPDATED");
    delay_ms(500);
    CmdLCD(CLEAR_LCD);
    StrLCD("                 ");
}
void changedate()
{
     u8 str[4];
    s32 var;
	u32 temp;
    do{
        CmdLCD(CLEAR_LCD);
        StrLCD("SET DATE - DD");
        temp=0;
        CmdLCD(GOTO_LINE2_POS0+temp);
        while(temp<2){
            key=Keyscan();
            if (key >= '0' && key <= '9'){
                CharLCD(key);
                str[temp]=key;
                temp++;
            }
            else if ((key == '#')&&(temp>0)){
                temp--;
                str[temp] = '\0';
                CmdLCD(GOTO_LINE2_POS0 + temp);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0  + temp);
            }
            while (ColScan() == 0);
        }
        str[temp] = '\0'; 
        var=atoi((const char *)str);
    }while(var<1 || var>31);
    date=var;
    var=0;
    do{
        CmdLCD(CLEAR_LCD);
        StrLCD("SET MONTH - MM");
        temp=0;
        CmdLCD(GOTO_LINE2_POS0+temp);
        while(temp<2){
            key=Keyscan();
            if (key >= '0' && key <= '9'){
                CharLCD(key);
                str[temp]=key;
                temp++;
            }
            else if ((key == '#')&&(temp>0)){
                temp--;
                str[temp] = '\0';
                CmdLCD(GOTO_LINE2_POS0 + temp);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0  + temp);
            }
            while (ColScan() == 0);
        }
        str[temp] = '\0';  
        var=atoi((const char *)str);
    }while(var<1 || var>12);
    month=var;
    var=0;
    CmdLCD(CLEAR_LCD);
    StrLCD("SET YEAR - YYYY");
    temp=0;
    CmdLCD(GOTO_LINE2_POS0+temp);
    while(temp<4){
        key=Keyscan();
        if (key >= '0' && key <= '9'){
            CharLCD(key);
            str[temp]=key;
            temp++;
        }
        else if ((key == '#')&&(temp>0)){
            temp--;
            str[temp] = '\0';
            CmdLCD(GOTO_LINE2_POS0 + temp);
            CharLCD(' ');
            CmdLCD(GOTO_LINE2_POS0  + temp);
        }
        while (ColScan() == 0);
		 }
		 str[temp] = '\0';         
    year=atoi((const char *)str);
		 SetRTCDateInfo(date,month,year);
		  CmdLCD(CLEAR_LCD);
    StrLCD("DATE UPDATED");
    CmdLCD(CLEAR_LCD);
    StrLCD("                ");
	 }
void readtime(u32 *time,u32 *lastkey)
{
  u32 j=0;
  CmdLCD(0xc0);
  StrLCD("              ");
  while(1)
  {
      key=Keyscan();
      if((key>='0')&&(key<='9'))
      {
         *time=(*time*10)+(key-48);
          CmdLCD(0xc0+j++);
          CharLCD(key);
          while(ColScan()==0);
      }
      else
      {
         *lastkey=key;
         CmdLCD(0xc0+j);
         CharLCD(*lastkey);
         while(ColScan()==0);
         break;
       }
   }
}
void changetime()
{
    u8 str[4];
    s32 var;
	  u32 temp;
    CmdLCD(CLEAR_LCD);
    do{
        CmdLCD(GOTO_LINE1_POS0);
        CmdLCD(GOTO_LINE1_POS0+2);
        StrLCD("SET HOURS-HH");
        temp=0;
        CmdLCD(GOTO_LINE2_POS0+temp);
        while(temp<2){
            key=Keyscan();
            if (key >= '0' && key <= '9'){
                CharLCD(key);
                str[temp]=key;
                temp++;
            }
            else if ((key == '#')&&(temp>0)){
                temp--;
                str[temp] = '\0';
                CmdLCD(GOTO_LINE2_POS0 + temp);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0  + temp);
            }
            while (ColScan() == 0);
        }
        str[temp] = '\0';
        var=atoi((const char *)str);
    }while(var<-1 || var>23);
    hour=var;
    var=0;
    CmdLCD(CLEAR_LCD);
    do{
        CmdLCD(GOTO_LINE1_POS0);
        CharLCD(0);
        CmdLCD(GOTO_LINE1_POS0+2);
        StrLCD("SET MINUTES-MM");
        temp=0;
        CmdLCD(GOTO_LINE2_POS0+temp);
        while(temp<2){
            key=Keyscan();
            if (key >= '0' && key <= '9'){
                CharLCD(key);
                str[temp]=key;
                temp++;
            }
            else if ((key == '#')&&(temp>0)){
                temp--;
                str[temp] = '\0';
                CmdLCD(GOTO_LINE2_POS0 + temp);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0  + temp);
            }
            while (ColScan() == 0);
        }
        str[temp] = '\0'; 

        var=atoi((const char *)str);
    }while(var<-1 || var>59);
    minute=var;
    var=0;
    CmdLCD(CLEAR_LCD);
    do{
        CmdLCD(GOTO_LINE1_POS0);
        CharLCD(0);
        CmdLCD(GOTO_LINE1_POS0+2);
        StrLCD("SET SECONDS-SS");
        temp=0;
        CmdLCD(GOTO_LINE2_POS0+temp);
        while(temp<2){
            key=Keyscan();
            if (key >= '0' && key <= '9'){
                CharLCD(key);
                str[temp]=key;
                temp++;
            }
            else if ((key == '#')&&(temp>0)){
                temp--;
                str[temp] = '\0';
                CmdLCD(GOTO_LINE2_POS0 + temp);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0  + temp);
            }
            while (ColScan() == 0);
        }
        str[temp] = '\0'; 
        var=atoi((const char *)str); 
    }while(var<-1 || var>59);
    second=var;
    SetRTCTimeInfo(hour,minute,second);
    CmdLCD(CLEAR_LCD);
    StrLCD("TIME UPDATED");
    CmdLCD(CLEAR_LCD);
    StrLCD("                ");
}
  void changemachinetime()
{
    u32 time=0,lastkey=0;

    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("enter new s_time");

    readtime(&time,&lastkey);

    if((time>0) && (time<24))
    {
        S_TIME = time;   // update only if valid
    }
    else
    {
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("wrong input");
        delay_s(2);
        // do NOT modify S_TIME
    }

    time=0;
    lastkey=0;

    CmdLCD(CLEAR_LCD);
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("enter new e_time");
    readtime(&time,&lastkey);
    if((time>0) && (time<24))
    {
        E_TIME = time;   // update only if valid
    }
    else
    {
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("wrong input");
        delay_s(1);
        // do NOT modify E_TIME
    }
}

void changepassword()
{
        u32 j=0;
        num=0;
        lastkey=0;
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("enter oldpassword:");
        key=Keyscan();
        readpassword(&num,&lastkey);
        CNT_P[i]='\0';
        if((strcmp((const char*)ORG_P,(const char*)CNT_P))==0)
        {
            u32 n=0,l=0;
            i=0;
            CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("--NEW PASSWORD--");
			 while(1)
            {
                 key=Keyscan();
                 delay_ms(100);
                 if((key>='0')&&(key<='9'))
                 {
                                                                           TMP_P[i++]=key;
                     n=(n*10)+(key-48);
                     CmdLCD(GOTO_LINE2_POS0+j++);
                     CharLCD(key);
                     while(ColScan()==0);
                 }
                 else if(key=='D')
                 {
                     l=key;
                     CmdLCD(GOTO_LINE2_POS0+j);
                     CharLCD(l);
                     while(ColScan()==0);
                     break;
                 }
                                                                 else if(key=='#')
                 {
                    delay_ms(100);
                    CmdLCD(GOTO_LINE2_POS0+--j);
                    StrLCD(" ");
                    i--;
                 }
        }
                                TMP_P[i]='\0';
        n=0,l=0;
        i=0,j=0;
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("--ENTER AGAIN--");
        while(1)
        {
           key=Keyscan();
           delay_ms(100);
		     if((key>='0')&&(key<='9'))
           {
               CNT_P[i++]=key;
               n=(n*10)+(key-48);
               CmdLCD(GOTO_LINE2_POS0+j++);
               CharLCD(key);
               while(ColScan()==0);
           }
           else if(key=='D')
           {
               l=key;
               CmdLCD(GOTO_LINE2_POS0+j);
               CharLCD(l);
               while(ColScan()==0);
               break;
           }
           else if(key=='#')
           {
               delay_ms(100);
               CmdLCD(GOTO_LINE2_POS0+--j);
               StrLCD(" ");
               i--;
           }
        }
        CNT_P[i]='\0';
      }
      if(strcmp((const char*)TMP_P,(const char*)CNT_P)==0)
     {
        strcpy(ORG_P,(const char*)TMP_P);
        ORG_P[strlen((char*)TMP_P)] = '\0';
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("password change");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("-----sucess-----");
        delay_s(1);
      }
      else
      {
	   CmdLCD(CLEAR_LCD);
          CmdLCD(GOTO_LINE1_POS0);
          StrLCD("password change");
          CmdLCD(GOTO_LINE2_POS0);
          StrLCD("-----failed-----");
          delay_s(1);
      }
}

void readpassword(u32 *num, u32 *lastkey)
{
    u32 j = 0;
    i = 0;
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("              ");
    *num = 0;
    while (1)
    {
        key = Keyscan();
        if (key >= '0' && key <= '9')
        {
            CNT_P[i++] = key;
            *num = (*num * 10) + (key - '0');
            CmdLCD(GOTO_LINE2_POS0 + j);
            CharLCD('*');
            j++;
            while (ColScan() == 0);
        }
        else if (key == '#')
        {
            if (i > 0)
            {
                i--;
                j--;
                CNT_P[i] = '\0';
                *num = (*num / 10);
                CmdLCD(GOTO_LINE2_POS0 + j);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0 + j);
            }
			  while (ColScan() == 0);
        }
        else
        {
            *lastkey = key;
            while (ColScan() == 0);
            break;
        }
    }
    CNT_P[i] = '\0';
}

int password()
{
        CmdLCD(CLEAR_LCD);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("---PASSWORD---");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("enter here:");
        delay_ms(200);
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("              ");
        readpassword(&num,&lastkey);
        CNT_P[i]='\0';
        if((strcmp((const char*)ORG_P,(const char *)CNT_P))==0)
        {
           return 1;
        }
        else
        {
           return 0;
        }

}

void init_system()
{
        Init_LCD();
        Init_kpm();
        Init_Interrupt();
		  RTC_Init();
}

int main()
{
   IODIR0|=1<<LED_PIN;
   IOCLR0=1<<LED_PIN;
   init_system();
   while(1)
   {
     CmdLCD(CLEAR_LCD);
     while(1)
     {
       GetRTCTimeInfo(&hour,&minute,&second);
			 CmdLCD(GOTO_LINE1_POS0);
       DisplayRTCTime(hour,minute,second);
       GetRTCDateInfo(&date,&month,&year);
			 CmdLCD(GOTO_LINE2_POS0);
       DisplayRTCDate(date,month,year);
       GetRTCDayInfo(&day);
			 CmdLCD(GOTO_LINE2_POS0+11);
       DisplayRTCDay(day);

       delay_ms(200);   // ? ADDED (Stops LCD blinking)

			 if(ColScan()==0)
			 {
				 key=Keyscan();
				 if(key=='*')
				 {
					 break;
				 }
			 }
       if((((IOPIN0>>ENT_SW)&1)==0))
       {
				  open_edit_menu();
          break;
       }
     }

     CmdLCD(CLEAR_LCD);
		 CmdLCD(GOTO_LINE1_POS0);
		 StrLCD("WELCOME....");
		 CmdLCD(GOTO_LINE2_POS0);
		 StrLCD("1:Enter Password");
		 key=Keyscan();

     if(key=='1')            
     {
			  GetRTCTimeInfo(&hour,&minute,&second);
        flag=password();

        if((flag==1)&&((hour>=S_TIME&&hour<E_TIME)))
        {
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD("--DEVICE ON--");

          // ? ADDED — BLINK LED FOR CORRECT PASSWORD
          for(b=0; b<5; b++)
          {
             IOSET0 =(1<<LED_PIN);
             delay_ms(200);
             IOCLR0 =(1<<LED_PIN);
             delay_ms(200);
          }

				}                                           

        else if(flag==0)
        {
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD("Wrong Password");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("--TRY AGAIN--");
          delay_s(1);
				}					

        else if((flag==1)&&(!(hour>=S_TIME&&hour<E_TIME)))
        {
          CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD("--SORRY--");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("This is not time");
					delay_s(1);
			  }
		 }
	}
}
