#include <lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "kpmdefines.h"

/* Keypad lookup table (4x4 matrix mapping physical keys to values) */
u8 KpmLUT[4][4] = {
    {1, 2, 3, 10},
    {4, 5, 6, 11},
    {7, 8, 9, 12},
    {13, 0, 14, 15}
};

/* Initialize keypad: configure row pins as output */
void InitKPM(void)
{
    /* Configure P1.16 to P1.19 as output (rows) */
    WRITENIBBLE(IODIR1, ROW0, 15);
}

/* Check if any column is active (key pressed or not) */
u8 ColScan(void)
{
    /* If any column bit is low → key pressed */
    if ((READNIBBLE(IOPIN1, COL0)) < 15)
        return 0;
    else
        return 1;
}

/* Find which row is active */
u8 RowCheck(void)
{
    u8 rno;

    for (rno = 0; rno <= 3; rno++)
    {
        /* Activate one row at a time */
        WRITENIBBLE(IOPIN1, ROW0, ~(1 << rno));

        if (ColScan() == 0)
        {
            break;   /* Row found */
        }
    }

    /* Reset rows */
    WRITENIBBLE(IOPIN1, ROW0, 0x0);

    return rno;
}

/* Find which column is active */
u8 ColCheck(void)
{
    u8 cno;

    for (cno = 0; cno <= 3; cno++)
    {
        /* Check each column pin */
        if (STATUSBIT(IOPIN1, (COL0 + cno)) == 0)
        {
            break;
        }
    }

    return cno;
}

/* Main keypad scanning function */
u8 KeyScan(void)
{
    u8 keyv, rno, cno;

    /* Wait until key is pressed */
    while (ColScan());

    /* Detect row */
    rno = RowCheck();

    /* Detect column */
    cno = ColCheck();

    /* Get actual key value from lookup table */
    keyv = KpmLUT[rno][cno];

    /* Wait until key is released */
    while (!ColScan());

    return keyv;
}

/* Read multi-digit number from keypad */
u32 ReadNum(void)
{
    u8 key;
    u32 sum = 0;

    while (1)
    {
        key = KeyScan();

        /* If numeric key pressed */
        if ((key >= 0) && (key <= 9))
        {
            sum = (sum * 10) + key;   /* Build number digit by digit */
        }
        else if (key == 16)          /* ENTER key */
        {
            break;
        }
    }

    return sum;
}
