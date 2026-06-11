#include "types.h"
#include "delay.h"
#include "adc_defines.h"
#include <lpc21xx.h>

f32 eAR;     /* stores analog voltage result */
u32 temp;    /* stores final temperature value */

/* ADC Initialization function */
void Init_ADC(void)
{
    PINSEL1 |= AIN1;                  /* Select ADC function for the pin (AIN1) */
    ADCR |= PDN_BIT | (CLKDIV << 8);  /* Power ON ADC and set clock divider */
}

/* Read ADC value from selected channel */
void Read_ADC(u32 chno, f32 *eAR, u32 *AdvDVal)
{
    ADCR &= ~(0xFF);                  /* Clear previous channel selection */
    ADCR |= chno | START_CONV;        /* Select ADC channel and start conversion */

    delay_us(3);                      /* Small delay for conversion stability */

    /* Wait until ADC conversion is completed */
    while (((ADGDR >> DONE_BIT) & 1) == 0);

    ADCR &= ~(START_CONV);            /* Stop conversion (optional depending on mode) */

    /* Extract 10-bit ADC result */
    *AdvDVal = ((ADGDR >> RESULT) & 0x3FF);

    /* Convert digital value to analog voltage */
    *eAR = (*AdvDVal * (3.3f / 1023.0f));
}

/* Function to read temperature value */
int read_temp(void)
{
    u32 AdvDVal;                      /* stores raw ADC digital value */

    /* Read ADC value from channel 1 (temperature sensor input) */
    Read_ADC(CH1, &eAR, &AdvDVal);

    /* Convert voltage to temperature (LM35: 10mV per degree Celsius) */
    temp = eAR * 100;

    return temp;                      /* return temperature in degree Celsius */
}
