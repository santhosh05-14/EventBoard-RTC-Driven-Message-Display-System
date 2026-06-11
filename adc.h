/* Initialize ADC module */
void Init_ADC(void);

/* Read ADC value from selected channel
   chno       -> ADC channel number
   eAR        -> pointer to store calculated analog voltage
   AdvDVal    -> pointer to store raw 10-bit ADC digital value */
void Read_ADC(u8 chno, f32 *eAR, u32 *AdvDVal);

/* Read temperature value from ADC and return in degree Celsius */
int read_temp(void);
