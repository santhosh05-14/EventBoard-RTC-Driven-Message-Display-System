#include "types.h"

/* Initialize keypad module (configure row/column pins) */
void InitKPM(void);

/* Check column status (returns 0 if key is pressed) */
u8 ColScan(void);

/* Detect active row in keypad matrix */
u8 RowCheck(void);

/* Detect active column in keypad matrix */
u8 ColCheck(void);

/* Scan and return key value from keypad */
u8 KeyScan(void);

/* Read multi-digit number from keypad input */
u32 ReadNum(void);
