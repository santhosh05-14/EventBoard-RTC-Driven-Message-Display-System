#include "types.h"

/* Initialize RTC module */
void RTC_Init(void);

/* Get current time from RTC (hour, minute, second) */
void GetRTCTimeInfo(s32*, s32*, s32*);

/* Display RTC time on LCD */
void DisplayRTCTime(u32, u32, u32);

/* Get current date from RTC (date, month, year) */
void GetRTCDateInfo(s32*, s32*, u32*);

/* Display RTC date on LCD */
void DisplayRTCDate(u32, u32, u32);

/* Set RTC time (hour, minute, second) */
void SetRTCTimeInfo(u32, u32, u32);

/* Set RTC date (date, month, year) */
void SetRTCDateInfo(u32, u32, u32);

/* Get day of week from RTC */
void GetRTCDay(s32*);

/* Display day of week on LCD */
void DisplayRTCDay(u32);

/* Set day of week */
void SetRTCDay(u32);

/* Read RTC hour register */
unsigned char rtc_hour(void);

/* Read RTC minute register */
unsigned char rtc_min(void);

/* Read RTC second register */
unsigned char rtc_sec(void);

/* Set individual time components */
void sethour(u8);
void setminute(u8);
void setsecond(u8);

/* Set individual date components */
void setdate(u8);
void setday(u8);
void setmonth(u8);
void setyear(u32);
