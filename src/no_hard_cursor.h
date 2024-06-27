#ifndef _INC_NO_HARD_CURSOR
#define _INC_NO_HARD_CURSOR

#define ARG_LENGTH_MAX 7
#define ARG_SIZE_MAX (ARG_LENGTH_MAX + 1)

#define HARD_CURSOR (0)
#define SOFT_CURSOR (-1)

// Mode options code.
#define MODE_INVALID_CODE (0x0000)
#define MODE_SOFT_CURSOR_CODE (0x0001)
#define MODE_HARD_CURSOR_CODE (0x0002)

#define MODE_SOFT_CURSOR_TXT ("soft")
#define MODE_HARD_CURSOR_TXT ("hard")


int parseArg(const char *arg);

#endif