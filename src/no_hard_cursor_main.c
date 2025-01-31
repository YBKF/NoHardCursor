#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "no_hard_cursor.h"

#undef __DEBUG
// #define __DEBUG

static int parsedOptCode = OPT_SOFT_CURSOR_CODE; // default option

static void usage(int status);

int main(int argc, char const *argv[])
{
    setProgramName(argv[0]);
    if (argc > 2)
    {
        fputs("Too many arguments.\n", stderr);
        usage(EXIT_FAILURE);
    }

    if (argc != 1)
        parsedOptCode = parseArgOpt(argv[1]);

    UINT uStateInfo;
    SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &uStateInfo, 0);

#ifdef __DEBUG
    printf("Before: %u\n", uStateInfo);
#endif

    switch (parsedOptCode)
    {
    case OPT_SOFT_CURSOR_CODE:
        if (uStateInfo != (UINT)SOFT_CURSOR)
            SystemParametersInfo(SPI_SETMOUSETRAILS, (UINT)SOFT_CURSOR, NULL, SPIF_UPDATEINIFILE);
        break;

    case OPT_HARD_CURSOR_CODE:
        if (uStateInfo != (UINT)HARD_CURSOR)
            SystemParametersInfo(SPI_SETMOUSETRAILS, (UINT)HARD_CURSOR, NULL, SPIF_UPDATEINIFILE);
        break;

    case OPT_HELP_USAGE_CODE:
        usage(EXIT_SUCCESS);
        break;

    case OPT_SHOW_SETTING_CODE:
        const char *optTXT;
        SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &uStateInfo, 0);
        if (uStateInfo == (UINT)SOFT_CURSOR)
            optTXT = OPT_SOFT_CURSOR_TXT_LONG;
        else
            optTXT = OPT_HARD_CURSOR_TXT_LONG;

        fprintf(stdout, "\
SPI_GETMOUSETRAILS\n\
param: %s (%u(UINT), %d(INT))\n",
                optTXT, uStateInfo, uStateInfo);
        break;

    default:
        fputs("ERROR: Invalid option code.\n", stderr);
        usage(EXIT_FAILURE);
    }

#ifdef __DEBUG
    SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &uStateInfo, 0);
    printf("After: %u\n", uStateInfo);
#endif

    return 0;
}

static void usage(int status)
{
    FILE *out = status ? stderr : stdout;

    const char *programName = getProgramName();

    fprintf(out, "\
Usage: %s [OPTION]\n",
            programName);
    fprintf(out, "\
Setting your mouse cursor rendering in Microsoft Windows.\n\
\n");

    fprintf(out, "\
With no parameter, will use software rendering cursor.\n\
\n");

    fprintf(out, "\
  [NULL], -s, --soft    Setting your cursor rendering method to software rendering\n");
    fprintf(out, "\
          -h, --hard    Setting your cursor rendering method to hardware rendering\n");
    fprintf(out, "\
              --show    Show current setting\n");
    fprintf(out, "\
              --help    Display this help and exit\n");
    fprintf(out, "\
\n");
    fprintf(out, "\
Examples:\n\
  %s -h     # Use hardware rendering cursor.\n\
  %s        # No parameter, use software rendering by default.\n",
            programName, programName);

    exit(status);
}