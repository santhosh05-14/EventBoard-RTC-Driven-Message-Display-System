#include "event.h"
#include "lcddefines.h"
#include "rtc.h"
#include "lcd.h"
#include <string.h>

/* Message database: scheduled event list */
message messageList[TOTAL_MESSAGES] =
{
    {7,45,"Good Morning! Classes Start Soon",1},
    {13,45,"C Programming Session in Classroom number 2",1},
    {10,15,"C module theory exam in 4th floor lab1",1},
    {10,15,"C module lab exam in 4th floor lab2",1},
    {12,45,"Lunch Break from 1PM–2PM",1},
    {9,45,"ARM Workshop on interrupts LAB1",1},
    {9,45,"ARM kit issue time middle lab",1},
    {15,15,"15 mins break for next ARM session",1},
    {17,0,"Revise today programs at home!",1},
    {17,45,"End of Day – See You Tomorrow!",1}
};

/* Function to scroll long message on LCD display */
void scrollMessage(char *msg)
{
    static int scrollpos  = 1;     /* Current scroll position */
    static int scrolltick = 0;     /* (Unused variable - can be removed) */

    char scroll[21];               /* 20 char LCD + null terminator */
    int len = 0, j;

    /* Calculate message length */
    while (msg[len]) len++;

    /* Create scrolling window */
    for (j = 0; j < 20; j++)
    {
        int src = j + scrollpos - 20;
        scroll[j] = (src >= 0 && src < len) ? msg[src] : ' ';
    }

    scroll[20] = '\0';

    /* Display scrolling text on LCD line 1 */
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD(scroll);

    scrollpos++;                   /* Move scroll forward */

    /* Reset scroll after full cycle */
    if (scrollpos > len + 20)
        scrollpos = 1;

    delay_ms(100);                 /* Scroll speed control */
}

/* Show remaining time before event starts */
void showRemainingTime(unsigned char hour, unsigned char min, unsigned char sec)
{
    int eventtime;
    int remaining;
    int rem_min, rem_sec;
    int i;
    int now;

    for(i = 0; i < TOTAL_MESSAGES; i++)
    {
        /* Read current RTC time */
        hour = rtc_hour();
        min  = rtc_min();
        sec  = rtc_sec();

        /* Convert current time to seconds */
        now = hour * 3600 + min * 60 + sec;

        /* Convert event time to seconds */
        eventtime = messageList[i].hour * 3600 +
                     messageList[i].minute * 60;

        /* 15-minute window before event */
        remaining = (eventtime + 900) - now;

        if(remaining > 0 && remaining <= 900)
        {
            /* Display scrolling event message */
            scrollMessage(messageList[i].text);

            /* Convert remaining seconds into MM:SS */
            rem_min = remaining / 60;
            rem_sec = remaining % 60;

            /* Display timer on LCD line 2 */
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("Time Left:");

            CharLCD((rem_min / 10) + '0');
            CharLCD((rem_min % 10) + '0');
            CharLCD(':');
            CharLCD((rem_sec / 10) + '0');
            CharLCD((rem_sec % 10) + '0');

            StrLCD("      ");   /* Clear leftover characters */

            delay_ms(10);
        }
    }
}

/* Display message if event matches current time */
void displaymessage(unsigned char hour, unsigned char minute, unsigned char second)
{
    int i;

    for(i = 0; i < TOTAL_MESSAGES; i++)
    {
        /* Check if event is enabled and time matches */
        if(messageList[i].enabled &&
           messageList[i].hour == hour &&
           messageList[i].minute == minute)
        {
            showRemainingTime(hour, minute, second);
        }
    }
}

/* Check if any message exists at given time */
int checkMessages(unsigned char hour, unsigned char minute)
{
    int i;

    for(i = 0; i < TOTAL_MESSAGES; i++)
    {
        if(messageList[i].hour == hour &&
           messageList[i].minute == minute)
        {
            return 1;   /* Message found */
        }
    }

    return 0;           /* No message found */
}

