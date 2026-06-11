#include <stdlib.h>
#include "lcddefines.h"
#include "lcd.h"
#include "kpm.h"
#include "rtc.h"
#include "event.h"
#include "delay.h"
#include "admin.h"

/* Function prototypes for internal menu handling */
void RTC_Edit();
void Event_Edit();

/* Admin mode menu (RTC edit / Event edit / Exit) */
void admin_Mode()
{
    u8 option;

    while(1)
    {
        CmdLCD(CLEAR_LCD);              /* Clear LCD screen */
        CmdLCD(GOTO_LINE1_POS0);        /* Move cursor to line 1 */
        StrLCD("1.RTC 2.EVENT");        /* Display main options */

        CmdLCD(GOTO_LINE2_POS0);        /* Move cursor to line 2 */
        StrLCD("3.EXIT");               /* Exit option */

        delay_ms(100);                  /* Small delay for stability */

        option = KeyScan();             /* Read keypad input */

        if(option)
        {
            if(option == 1)
                RTC_Edit();             /* Enter RTC edit mode */

            else if(option == 2)
                Event_Edit();           /* Enter event edit mode */

            else if(option == 3)
                break;                  /* Exit admin mode */
        }
    }
}

/* Function to get multi-digit input (up to 4 digits) from keypad */
u16 get4DigitInput()
{
    u8 d1, d2 = 0, d3 = 0, d4 = 0;
    u16 value;
    u8 key;

    /* First digit (mandatory input) */
    while((d1 = KeyScan()) == 0);

    if(d1 <= 9)
        CharLCD(d1 + '0');

    /* Second digit or ENTER */
    while(1)
    {
        key = KeyScan();

        if(key == 15)   /* ENTER key */
            return d1;

        if(key <= 9)
        {
            d2 = key;
            CharLCD(d2 + '0');
            break;
        }
    }

    /* Third digit or ENTER */
    while(1)
    {
        key = KeyScan();

        if(key == 15)   /* ENTER key */
            return (d1 * 10) + d2;

        if(key <= 9)
        {
            d3 = key;
            CharLCD(d3 + '0');
            break;
        }
    }

    /* Fourth digit or ENTER */
    while(1)
    {
        key = KeyScan();

        if(key == 15)   /* ENTER key */
            return (d1 * 100) + (d2 * 10) + d3;

        if(key <= 9)
        {
            d4 = key;
            CharLCD(d4 + '0');
            break;
        }
    }

    /* Wait for final ENTER after 4 digits */
    while(KeyScan() != 15);

    value = (d1 * 1000) + (d2 * 100) + (d3 * 10) + d4;

    return value;
}

/* RTC edit menu (hour/min/sec/date/day/month/year settings) */
void RTC_Edit()
{
    u8 option;
    u8 value;

    while(1)
    {
        CmdLCD(CLEAR_LCD);              /* Clear LCD */

        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.H 2.M 3.S 4.D");     /* First line menu */

        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("5.D 6.M 7.Y 8.EX");     /* Second line menu */

        option = KeyScan();            /* Get user selection */

        if(option)
        {
            switch(option)
            {
                case 1:   /* Hour setting */
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Enter Hour:");
                    value = get2DigitInput();

                    if(value <= 23)
                        sethour(value);

                    delay_ms(1000);
                    break;

                case 2:   /* Minute setting */
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Enter Min:");
                    value = get2DigitInput();

                    if(value <= 59)
                        setminute(value);

                    delay_ms(1000);
                    break;

                case 3:   /* Second setting */
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Enter Sec:");
                    value = get2DigitInput();

                    if(value <= 59)
                        setsecond(value);

                    delay_ms(1000);
                    break;

                case 4:   /* Date setting */
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Enter Date:");
                    value = get4DigitInput();

                    if(value >= 1 && value <= 31)
                        setdate(value);

                    delay_ms(1000);
                    break;

                case 5:   /* Day setting */
                    CmdLCD(CLEAR_LCD);
                    StrLCD("0SUN-6SAT");

                    value = KeyScan();
                    CharLCD(value + '0');

                    if(value >= 0 && value <= 6)
                        setday(value);

                    delay_ms(1000);
                    break;

                case 6:   /* Month setting */
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Enter Month(1-12):");

                    value = get4DigitInput();

                    if(value >= 1 && value <= 12)
                        setmonth(value);

                    delay_ms(1000);
                    break;

                case 7:   /* Year setting */
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Enter Year:");

                    value = get4DigitInput();
                    setyear(value);

                    delay_ms(1000);
                    break;

                case 8:   /* Exit RTC menu */
                    return;
            }
        }
    }
}

/* Event enable/disable menu */
void Event_Edit()
{
    u8 key, event_no;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ENTER EVENT NO(0-9)");

        event_no = KeyScan();          /* Select event number */

        CmdLCD(GOTO_LINE2_POS0);
        CharLCD(event_no + '0');

        if(event_no <= 9)
        {
            CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("1.ACT 2.DEACT");

            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("3.EXIT");

            key = KeyScan();           /* Action selection */

            if(key == 1)
            {
                messageList[event_no].enabled = 1; /* Activate event */
                return;
            }
            else if(key == 2)
            {
                messageList[event_no].enabled = 0; /* Deactivate event */
                return;
            }
            else if(key == 3)
            {
                return;                 /* Exit menu */
            }
        }
        else
        {
            CmdLCD(CLEAR_LCD);
            StrLCD("INVALID");
            delay_ms(1000);
            return;
        }
    }
}
