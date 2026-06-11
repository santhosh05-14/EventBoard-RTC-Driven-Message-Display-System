#include "types.h"

/* Write raw data byte to LCD */
void WriteLCD(u8 data);

/* Send command to LCD */
void CmdLCD(u8 cmd);

/* Send single character to LCD */
void CharLCD(u8 ascii);

/* Initialize LCD (8-bit mode configuration) */
void InitLCD(void);

/* Display string on LCD */
void StrLCD(char* str);

/* Display unsigned 32-bit number */
void U32LCD(u32 n);

/* Display signed 32-bit number */
void S32LCD(s32 n);

/* Display binary number with specified bit width */
void BinLCD(u32 n, u8 nbd);

/* Create and load custom character into CGRAM */
void BuildCGRAM(u8* p, u8 nBytes);

/* Display floating point number with decimal precision */
void f32LCD(f32 fnum, u8 ndp);

/* Display octal number */
void OctLCD(u32 n);

/* Display hexadecimal number */
void HexLCD(u32 n);
