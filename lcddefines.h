/* LCD data pins connected to P0.8 to P0.15 */
#define LCD_DATA 8      /* Start pin P0.8 */

/* LCD control pins */
#define RS 16           /* Register Select pin P0.16 */
#define RW 18           /* Read/Write pin P0.18 */
#define EN 17           /* Enable pin P0.17 */

/* LCD command set */

/* Clear display */
#define CLEAR_LCD        0x01

/* Return cursor to home position */
#define RET_CUR_HOME     0x02

/* 4-bit mode commands */
#define MODE_4BIT_1LINE  0x20
#define MODE_4BIT_2LINE  0x28

/* 8-bit mode commands */
#define MODE_8BIT_1LINE  0x30
#define MODE_8BIT_2LINE  0x38

/* Display control commands */
#define DISP_OFF         0x08
#define DISP_ON_CUR_OFF  0x0C
#define DISP_ON_CUR_ON   0x0E
#define DISP_ON_CUR_BLINK 0x0F

/* Cursor positioning */
#define GOTO_LINE1_POS0  0x80
#define GOTO_LINE2_POS0  0xC0

/* CGRAM address */
#define GOTO_CGRAM       0x40

/* Entry mode set (cursor move direction) */
#define SHIFT_CUR_RIGHT  0x06

