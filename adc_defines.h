#define FOSC 12000000            /* Crystal oscillator frequency = 12 MHz */
#define CCLK (5 * FOSC)          /* CPU clock = 5 × oscillator frequency */
#define PCLK (CCLK / 4)          /* Peripheral clock = CCLK / 4 */
#define ADCLK 3000000            /* Desired ADC clock = 3 MHz */
#define CLKDIV ((PCLK / ADCLK) - 1)  /* ADC clock divider value */

/* ADC Channel selection masks */
#define CH0 0x01                 /* Select ADC channel 0 */
#define CH1 0x02                 /* Select ADC channel 1 */
#define CH2 0x04                 /* Select ADC channel 2 */
#define CH3 0x08                 /* Select ADC channel 3 */

/* ADC Control bits */
#define PDN_BIT   (1 << 21)      /* ADC power-down control bit (0 = power down, 1 = enable) */
#define START_CONV (1 << 24)     /* Start ADC conversion */
#define RESULT     6             /* ADC result bit position in data register */
#define DONE_BIT   31            /* ADC conversion completion flag bit */

/* Pin function selection for ADC inputs */
#define AIN0 0x00400000          /* Analog input 0 pin select */
#define AIN1 0x01000000          /* Analog input 1 pin select */
#define AIN2 0x04000000          /* Analog input 2 pin select */
#define AIN3 0x10000000          /* Analog input 3 pin select */
