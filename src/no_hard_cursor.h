#ifndef _INC_NO_HARD_CURSOR
#define _INC_NO_HARD_CURSOR

#define ARG_LENGTH_MAX 7
#define ARG_SIZE_MAX (ARG_LENGTH_MAX + 1)

#define HARD_CURSOR (0)
#define SOFT_CURSOR (-1)

/* Options code. */
#define OPT_INVALID_CODE (0x0000)
#define OPT_SOFT_CURSOR_CODE (0x0001)
#define OPT_HARD_CURSOR_CODE (0x0002)
#define OPT_HELP_USAGE_CODE (0x0003)
#define OPT_SHOW_SETTING_CODE (0x0004)

/* Long options. */
//      OPT_INVALID_CODE (NULL)
#define OPT_SOFT_CURSOR_TXT_LONG ("soft")
#define OPT_HARD_CURSOR_TXT_LONG ("hard")
#define OPT_HELP_USAGE_TXT_LONG ("help")
#define OPT_SHOW_SETTING_TXT_LONG ("show")

/* Short options. */
//      OPT_INVALID_TXT_SHORT (0)
#define OPT_SOFT_CURSOR_TXT_SHORT ('s')
#define OPT_HARD_CURSOR_TXT_SHORT ('h')
//      OPT_HELP_USAGE_TXT_SHORT (0)
//      OPT_SHOW_SETTING_TXT_LONG (0)

void setProgramName(const char *programName);
const char *getProgramName();
int parseArgOpt(const char *arg);
// int parseArg(const char *arg);

#endif