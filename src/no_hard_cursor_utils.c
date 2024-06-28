#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "no_hard_cursor.h"

#define ARG_TYPE_SINGLE (0x0010)
#define ARG_TYPE_LONG (0x0011)

/**
 * 检查参数是否合规，
 * 合规，则返回字符串参数在 "-" 或 "--" 之后的首地址，并将参数类型存储到 argType 中；
 * 不合规，则返回 NULL 且 argType == EOF
 *
 * 检测参数是否符合规则，以下为参数检测规则（[]表示一个单元）：
 * "-"  : ['-'] + [任意字符] + ['\0']
 * "--" : ['-'] + ['-'] + [任意字符串]
 *
 * 检测两种识别方式：
 * "-"  : 仅识别一个字符，argType = ARG_TYPE_SINGLE
 * "--" : 识别一个字符串，argType = ARG_TYPE_LONG
 *
 * 将检测完毕后的参数类型存储到 *argType 中，
 * argType == ARG_TYPE_SINGLE, 表示参数类型为单字符；
 * argType == ARG_TYPE_LONG, 表示参数类型为长字符。
 * argType == EOF, 表示参数类型识别错误
 *
 * 此函数并不检测 "-" 或 "--" 之后是否为有效字符，仅检测参数是否符合规则，
 * 符合规则，便返回 "-" 或 "--" 之后的字符串的地址；若不符合规则，则返回 NULL。
 */
static const char *checkArgFormat(const char *arg, int *argType)
{
    if (arg == NULL || argType == NULL)
        return NULL;

    const char *pCurrentCheck = arg;

    // 首先，检测第一个字符是否为 '-'
    //  [?] [?] [?]
    //   ^
    if (*pCurrentCheck == '-')
    {
        pCurrentCheck++;

        // 然后，检测下一个字符是否为 '-'，
        // 为 '-' 则表示参数为字符串（多字符），
        // 否则，表示参数为单字符
        //  [-] [?] [?]
        //       ^
        if (*pCurrentCheck == '-')
        {
            *argType = ARG_TYPE_LONG;
            // 参数为多字符，匹配成功，返回参数字符串 "--" 后的地址
            //  [-] [-] [*]
            //           ^
            return ++pCurrentCheck;
        }
        else if (*(pCurrentCheck + 1) == '\0')
        {
            *argType = ARG_TYPE_SINGLE;
            // 不管 pCurrentCheck 当前位置是什么，只要下一个位置是空字符，便表示参数为单字符，匹配成功，返回这个字符的地址
            //  [-] [*] [\0]
            //       ^
            return pCurrentCheck;
        }
    }

    // 未匹配到预期格式，则返回 NULL，且参数类型设为 EOF 表示遇到匹配错误
    *argType = EOF;
    return NULL;
}

/**
 * 解析检查后的参数，并返回参数对应的模式的代表值:
 * OPT_INVALID_CODE         (0x0000)
 * OPT_SOFT_CURSOR_CODE     (0x0001)
 * OPT_HARD_CURSOR_CODE     (0x0002)
 * OPT_HELP_USAGE_CODE      (0x0003)
 *
 * 若函数运行过程中出错，则返回EOF
 */
int parseArgOpt(const char *arg)
{
    if (arg == NULL)
        return EOF;

    int argType;
    const char *checkedArg;
    int parsedOptCode;

    if ((checkedArg = checkArgFormat(arg, &argType)) == NULL)
    {
        fputs("ERROR: Invalid argument.\n", stderr);

        if (argType == EOF)
            fputs("ERROR: Invalid argument formation.\n", stderr);

        return OPT_INVALID_CODE;
    }

    // 参数已经过检查且符合格式
    if (argType == ARG_TYPE_SINGLE)
    {
        switch (*checkedArg)
        {
        case OPT_SOFT_CURSOR_TXT_SHORT:
            parsedOptCode = OPT_SOFT_CURSOR_CODE;
            break;

        case OPT_HARD_CURSOR_TXT_SHORT:
            parsedOptCode = OPT_HARD_CURSOR_CODE;
            break;

        default:
            fprintf(stderr, "ERROR: Invalid mode: %s\n", checkedArg);
            parsedOptCode = OPT_INVALID_CODE;
            break;
        }
    }
    else if (argType == ARG_TYPE_LONG)
    {
        if (strncmp(checkedArg, OPT_SOFT_CURSOR_TXT_LONG, ARG_LENGTH_MAX) == 0)
        {
            parsedOptCode = OPT_SOFT_CURSOR_CODE;
        }
        else if (strncmp(checkedArg, OPT_HARD_CURSOR_TXT_LONG, ARG_LENGTH_MAX) == 0)
        {
            parsedOptCode = OPT_HARD_CURSOR_CODE;
        }
        else if (strncmp(checkedArg, OPT_HELP_USAGE_TXT_LONG, ARG_LENGTH_MAX) == 0)
        {
            parsedOptCode = OPT_HELP_USAGE_CODE;
        }
        else
        {
            fprintf(stderr, "ERROR: Invalid mode: %s\n", checkedArg);
            parsedOptCode = OPT_INVALID_CODE;
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Invalid argument type: %d\n", argType);
        return EOF;
    }

    return parsedOptCode;
}

// /**
//  * 解析检查后的参数，并返回参数对应的选项的代表值
//  *
//  * HARD_CURSOR (0)
//  * SOFT_CURSOR (-1)
//  *
//  */
// int parseArg(const char *arg)
// {
//     // 参数为空指针
//     if (arg == NULL)
//     {
//         fputs("ERROR: null argument.\n", stderr);
//         exit(EXIT_FAILURE);
//     }

//     int parsedOptCode;

//     // 参数解析函数遇到错误
//     if ((parsedOptCode = parseArgOpt(arg)) == EOF)
//     {
//         fputs("ERROR: Failed to parse the argument.\n", stderr);
//         exit(EXIT_FAILURE);
//     }

//     switch (parsedOptCode)
//     {
//     case OPT_SOFT_CURSOR_CODE:
//         return SOFT_CURSOR;

//     case OPT_HARD_CURSOR_CODE:
//         return HARD_CURSOR;

//     default:
//         fputs("ERROR: Invalid option code.\n", stderr);
//         exit(EXIT_FAILURE);
//     }
// }