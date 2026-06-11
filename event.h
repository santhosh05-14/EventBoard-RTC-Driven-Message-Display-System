#define TOTAL_MESSAGES 10     /* Total number of scheduled messages */

/* Structure to store event details */
typedef struct
{
    unsigned char hour;      /* Event hour */
    unsigned char minute;    /* Event minute */
    char text[80];           /* Event message text */
    unsigned char enabled;   /* 1 = enabled, 0 = disabled */
} message;

/* Global event list defined in another file */
extern message messageList[TOTAL_MESSAGES];

/* Function to scroll long message on LCD */
void scrollMessage(char *msg);

/* Function to display message based on current time */
void displaymessage(unsigned char hour,
                    unsigned char minute,
                    unsigned char second);

/* Function to check if any message exists at given time */
int checkMessages(unsigned char hour,
                  unsigned char minute);

/* Function to show remaining time for event */
void showRemainingTime(unsigned char hour,
                        unsigned char min,
                        unsigned char sec);
