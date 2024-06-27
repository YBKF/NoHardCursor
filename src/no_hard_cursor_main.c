#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "no_hard_cursor.h"

// default option: SOFT_CURSOR
static UINT mode = SOFT_CURSOR;

int main(int argc, char const *argv[])
{
    if (argc > 2)
    {
        fputs("Too many arguments.\n", stderr);
        exit(EXIT_FAILURE);
    }

    UINT uStateInfo;

    SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &uStateInfo, 0);

    // printf("Before: %u\n", uStateInfo);

    if (argc != 1)
        mode = parseArg(argv[1]);

    if (uStateInfo != (UINT)mode)
        SystemParametersInfo(SPI_SETMOUSETRAILS, (UINT)mode, NULL, SPIF_UPDATEINIFILE);

    // SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &uStateInfo, 0);
    // printf("After: %u\n", uStateInfo);

    return 0;
}
