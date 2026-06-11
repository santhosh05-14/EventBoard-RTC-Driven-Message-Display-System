#include <lpc214x.h>
#include "lcddefines.h"
#include "rtc.h"
#include "lcd.h"
#include "kpm.h"
#include "event.h"
#include "types.h"
#include "delay.h"
#include "adc.h"

#define SW (1 << 24)   /* Switch connected to P1.24 */

u32 temperature;      /* Stores ADC-based temperature value */

int main()
{
    s32 hour, min, sec, date, month, year, day;
    int holdcount = 0;
    char msg;

    InitLCD();         /* Initialize LCD display */
    RTC_Init();        /* Initialize RTC module */
    InitKPM();         /* Initialize keypad */
    Init_ADC();        /* Initialize ADC */

    /* RTC clock calibration registers */
    CCR = 1 << 1;      /* Disable RTC */
    PREINT = 456;      /* Integer part for clock */
    PREFRAC = 25024;   /* Fractional part for clock */

    /* Set initial date and time */
    SetRTCTimeInfo(8, 58, 00);
    SetRTCDateInfo(13, 03, 2026);
    SetRTCDay(5);

    CCR = 1 << 0;      /* Enable RTC */

    while(1)
    {
        /* Read current RTC time */
        GetRTCTimeInfo(&hour, &min, &sec);
        GetRTCDay(&day);
        GetRTCDateInfo(&date, &month, &year);

        /* Check admin switch press */
        if(!(IOPIN1 & SW))
        {
            delay_ms(10);     /* Debounce delay */
            holdcount++;      /* Count long press */

            if(holdcount >= 20)
            {
                admin_Mode(); /* Enter admin mode */
                holdcount = 0;
            }
        }

        /* Check if any scheduled message exists */
        if(checkMessages(hour, min))
        {
            displaymessage(hour, min, sec); /* Show event message */
        }
        else
        {
            /* Display RTC time on LCD line 1 */
            CmdLCD(GOTO_LINE1_POS0);

            DisplayRTCTime(hour, min, sec);
            StrLCD("  ");
            DisplayRTCDay(day);

            /* Display date + temperature on LCD line 2 */
            CmdLCD(GOTO_LINE2_POS0);

            DisplayRTCDate(date, month, year);

            temperature = read_temp();   /* Read ADC temperature */

            StrLCD(" ");
            U32LCD(temperature);         /* Display temperature */

            CharLCD(223);                /* Degree symbol */
            CharLCD('C');                /* Celsius */

            delay_ms(500);               /* Refresh delay */
        }
    }
}
