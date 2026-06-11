#include "defines.h"
#include "types.h"
#include <lpc21xx.h>
#include "lcddefines.h"
#include "delay.h"

/* Write raw data/command byte to LCD */
void WriteLCD(u8 data)
{
    SCLRBIT(IOCLR0, RW);          /* RW = 0 → write mode */

    WRITEBYTE(IOPIN0, LCD_DATA, data);  /* Send data to LCD data pins */

    SSETBIT(IOSET0, EN);          /* EN = 1 → latch data */
    delay_us(1);                  /* Enable pulse delay */

    SCLRBIT(IOCLR0, EN);          /* EN = 0 → complete write cycle */
    delay_ms(2);                  /* LCD internal processing delay */
}

/* Send command to LCD */
void CmdLCD(u8 cmd)
{
    SCLRBIT(IOCLR0, RS);          /* RS = 0 → command register select */
    WriteLCD(cmd);                /* Write command to LCD */
}

/* Send character/data to LCD */
void CharLCD(u8 ascii)
{
    SSETBIT(IOSET0, RS);          /* RS = 1 → data register select */
    WriteLCD(ascii);              /* Write ASCII character */
}

/* Initialize LCD in 8-bit mode */
void InitLCD(void)
{
    /* Configure data pins P0.8 to P0.15 as output */
    WRITEBYTE(IODIR0, LCD_DATA, 0xFF);

    /* Configure control pins as output */
    SETBIT(IODIR0, RS);
    SETBIT(IODIR0, RW);
    SETBIT(IODIR0, EN);

    delay_ms(15);                 /* LCD power-on delay */

    /* Initialization sequence */
    CmdLCD(MODE_8BIT_1LINE);
    delay_ms(5);

    CmdLCD(MODE_8BIT_1LINE);
    delay_us(100);

    CmdLCD(MODE_8BIT_1LINE);

    CmdLCD(MODE_8BIT_2LINE);      /* 2-line mode */
    CmdLCD(DISP_ON_CUR_OFF);      /* Display ON, cursor OFF */
    CmdLCD(CLEAR_LCD);            /* Clear display */
    CmdLCD(SHIFT_CUR_RIGHT);      /* Entry mode */
}

/* Display string on LCD */
void StrLCD(char* str)
{
    while(*str)
    {
        CharLCD(*str++);          /* Send each character */
    }
}

/* Display unsigned 32-bit number */
void U32LCD(u32 n)
{
    u8 a[10];
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            a[i++] = (n % 10) + '0';   /* Convert digit to ASCII */
            n /= 10;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);             /* Print in reverse */
        }
    }
}

/* Display signed 32-bit number */
void S32LCD(s32 n)
{
    if(n < 0)
    {
        CharLCD('-');              /* Print sign */
        n = -n;
    }

    U32LCD(n);                     /* Print magnitude */
}

/* Display binary number */
void BinLCD(u32 n, u8 nbd)
{
    s32 i;

    for(i = (nbd - 1); i >= 0; i--)
    {
        CharLCD(((n >> i) & 1) + '0');  /* Extract each bit */
    }
}

/* Write custom character into CGRAM */
void BuildCGRAM(u8* p, u8 nBytes)
{
    s32 i;

    CmdLCD(GOTO_CGRAM);            /* Switch to CGRAM */

    for(i = 0; i < nBytes; i++)
    {
        CharLCD(p[i]);             /* Load pattern bytes */
    }

    CmdLCD(GOTO_LINE2_POS0);       /* Return to DDRAM */
}

/* Display floating-point number */
void f32LCD(f32 fnum, u8 ndp)
{
    u32 inum;

    if(fnum < 0.0)
    {
        CharLCD('-');              /* Print sign */
        fnum = -fnum;
    }

    inum = fnum;
    U32LCD(inum);                  /* Integer part */
    CharLCD('.');                  /* Decimal point */

    while(ndp)
    {
        fnum = (fnum - inum) * 10;
        inum = fnum;
        CharLCD(inum + '0');       /* Fraction digits */
        ndp--;
    }
}

/* Display hexadecimal number */
void HexLCD(u32 n)
{
    u8 a[8], rem;
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            rem = n % 16;
            (rem < 10) ? (rem += '0') : (rem += 55);
            a[i++] = rem;
            n /= 16;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}

/* Display octal number */
void OctLCD(u32 n)
{
    s32 i = 0;
    u8 a[12];

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n)
        {
            a[i++] = (n % 8) + '0';   /* Convert to octal digit */
            n /= 8;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}
