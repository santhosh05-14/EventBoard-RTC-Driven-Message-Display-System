/* Set a particular bit in a word */
#define SETBIT(WORD, BP)        (WORD |= (1 << BP))

/* Clear a particular bit in a word */
#define CLRBIT(WORD, BP)        (WORD &= ~(1 << BP))

/* Check status of a bit (returns 0 or 1) */
#define STATUSBIT(WORD, BP)     ((WORD >> BP) & 1)

/* Write a specific bit value (0 or 1) at a position */
#define WRITEBIT(WORD, BP, BIT) (WORD = ((WORD & ~(1 << BP)) | (BIT << BP)))

/* Write 4-bit nibble at given start position */
#define WRITENIBBLE(WORD, SBP, NIBBLE) \
    (WORD = ((WORD & ~(0xF << SBP)) | (NIBBLE << SBP)))

/* Write 8-bit byte at given start position */
#define WRITEBYTE(WORD, SBP, BYTE) \
    (WORD = ((WORD & ~(0xFF << SBP)) | (BYTE << SBP)))

/* Write 16-bit half word at given start position */
#define WRITEHWORD(WORD, SBP, HWORD) \
    (WORD = ((WORD & ~(0xFFFF << SBP)) | (HWORD << SBP)))

/* Read 4-bit nibble from given position */
#define READNIBBLE(WORD, SBP)   ((WORD >> SBP) & 0xF)

/* Force set bit (overwrites entire word incorrectly as per current logic) */
#define SSETBIT(WORD, BP)       (WORD = (1 << BP))

/* Force clear bit (NOTE: actually sets bit instead of clearing — likely bug) */
#define SCLRBIT(WORD, BP)       (WORD = (1 << BP))
