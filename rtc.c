// rtc.c
#include <LPC21xx.h>
#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"

s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/* ----------------------------------------------------------
   RTC INITIALIZATION  (FULLY CORRECTED)
   ---------------------------------------------------------- */
void RTC_Init(void)
{
    // STOP RTC
    CCR = 0x00;

    // RESET counters
    CCR = RTC_RESET;   // bit1 = 1

    // Prescaler load values
    PREINT  = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;

    // START RTC (CLKEN=1, CTCRST=1)
    CCR = RTC_ENABLE | RTC_RESET;   // 0x03
}

/* ----------------------------------------------------------
    RTC READ FUNCTIONS
   ---------------------------------------------------------- */
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
    *hour   = HOUR;
    *minute = MIN;
    *second = SEC;
}

void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
    CharLCD((hour/10)+48);
    CharLCD((hour%10)+48);
    CharLCD(':');
    CharLCD((minute/10)+48);
    CharLCD((minute%10)+48);
    CharLCD(':');
    CharLCD((second/10)+48);
    CharLCD((second%10)+48);
}

void GetRTCDateInfo(u32 *date, u32 *month, u32 *year)
{
    *date  = DOM;
    *month = MONTH;
    *year  = YEAR;
}

void DisplayRTCDate(u32 date, u32 month, u32 year)
{
    CharLCD((date/10)+48);
    CharLCD((date%10)+48);
    CharLCD('/');
    CharLCD((month/10)+48);
    CharLCD((month%10)+48);
    CharLCD('/');
    U32LCD(year);
}

void GetRTCDayInfo(s32 *day)
{
    *day = DOW;
}

void DisplayRTCDay(u32 day)
{
    StrLCD(week[day]);
}

/* ----------------------------------------------------------
    RTC WRITE FUNCTIONS  (FULLY FIXED)
   ---------------------------------------------------------- */

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
    CCR = 0x00; // STOP RTC

    SEC  = second;
    MIN  = minute;
    HOUR = hour;

    CCR = RTC_ENABLE | RTC_RESET;  // START RTC
}

void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
    CCR = 0x00;

    DOM   = date;
    MONTH = month;
    YEAR  = year;

    CCR = RTC_ENABLE | RTC_RESET;
}

void SetRTCDay(u32 day)
{
    CCR = 0x00;

    DOW = day;

    CCR = RTC_ENABLE | RTC_RESET;
}
