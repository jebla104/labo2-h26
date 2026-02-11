//
// Created by leodumont444 on 2024-11-01
// Project: Raytracer
// Details: Debug log utilities
//

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <time.h>
#include <string.h>

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_CYAN "\x1b[36m"

static inline char *get_timestamp()
{
    static char buffer[20];
    time_t timer;
    struct tm *tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 20, "%H:%M:%S", tm_info);
    return buffer;
}

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define DEBUG_MODE 1

#ifdef DEBUG_MODE

// [TIME] [FILE:LINE] [FUNC] MESSAGE
#define LOG(fmt, ...)                                              \
    do                                                             \
    {                                                              \
        fprintf(stderr, "%s[%s]%s %s[%s:%d]%s %s[%s]%s " fmt "\n", \
                COLOR_CYAN, get_timestamp(), COLOR_RESET,          \
                COLOR_YELLOW, __FILENAME__, __LINE__, COLOR_RESET, \
                COLOR_BLUE, __func__, COLOR_RESET,                 \
                ##__VA_ARGS__);                                    \
    } while (0)

#else
#define LOG(fmt, ...) \
    do                \
    {                 \
    } while (0)
#endif

#endif // DEBUG_H