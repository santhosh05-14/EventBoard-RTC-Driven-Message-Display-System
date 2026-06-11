#include "types.h"

/* Microsecond delay function */
void delay_us(u32 tdly)
{
    tdly *= 12;          /* Calibrated loop count for 1 microsecond delay */
    while(tdly--);       /* Busy-wait loop */
}

/* Millisecond delay function */
void delay_ms(u32 tdly)
{
    tdly *= 12000;       /* Calibrated loop count for 1 millisecond delay */
    while(tdly--);       /* Busy-wait loop */
}

/* Second delay function */
void delay_s(u32 tdly)
{
    tdly *= 12000000;    /* Calibrated loop count for 1 second delay */
    while(tdly--);       /* Busy-wait loop */
}
