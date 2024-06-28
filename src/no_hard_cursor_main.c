#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "no_hard_cursor.h"

#undef __DEBUG
#define __DEBUG_

// default option: SOFT_CURSOR
static int parsedOptCode = OPT_SOFT_CURSOR_CODE;

/**
 * 解析参数(分辨长短参数, 并去除参数前缀) -> 识别参数(根据参数针对到具体选项代号) -> 接受代号, 执行功能
 */

int main(int argc, char const *argv[])
{
    if (argc > 2)
    {
        fputs("Too many arguments.\n", stderr);
        exit(EXIT_FAILURE);
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
        // TODO: usage();
        break;

    default:
        fputs("ERROR: Invalid option code.\n", stderr);
        exit(EXIT_FAILURE);
    }

#ifdef __DEBUG
    SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &uStateInfo, 0);
    printf("After: %u\n", uStateInfo);
#endif

    return 0;
}
