/* Copyright © 2013 Paulo Roberto Urio */
#ifndef DEBUG_H_
#define DEBUG_H_

#include <cstdio>
#include <cstring>

/* Debugging levels */
#define TESTING 0
#define INFO 10
#define WARN 20
#define ERROR 30

/* Controls the verbosity of DEBUG macro */
#ifndef DEBUG_VERBOSITY
#define DEBUG_VERBOSITY INFO
#endif

/* Controls whether debug() should print colorful messages or not */
#ifndef COLORED_DEBUG
#define COLORED_DEBUG 1
#endif

#if COLORED_DEBUG == 1
#define __debug_msg_end_tag "\033[0m"
#define __debug_msg_color_TESTING "\033[1m"
#define __debug_msg_color_INFO "\033[1;34m"
#define __debug_msg_color_WARN "\033[1;33m"
#define __debug_msg_color_ERROR "\033[1;31m"
#else
#define __debug_msg_end_tag
#define __debug_msg_color_TESTING
#define __debug_msg_color_INFO
#define __debug_msg_color_WARN
#define __debug_msg_color_ERROR
#endif

#define __debug_msg_TESTING "Debug: "
#define __debug_msg_INFO "Info: "
#define __debug_msg_WARN "Warn: "
#define __debug_msg_ERROR "Error: "

#define __SHORT_FORM_OF_FILE__ \
        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define __print_debug(level, preamble, fmt, ...) \
    if (level >= DEBUG_VERBOSITY) { \
        fprintf(stderr, "%s:%d:%s(): " preamble fmt __debug_msg_end_tag, \
                __SHORT_FORM_OF_FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
        fflush(stderr); }

/*
 * Print a message respecting the verbosity level set during compiling
 * This macro should be use to print messages that doesn't fit as
 * program output data, but for information, warning and errors.
 */
#define printd(level, ...) \
    do { __print_debug(level, __debug_msg_color_ ## level \
            __debug_msg_ ## level, ##__VA_ARGS__); } while (0)

/* Debug macro.  Only generate code inside DEBUG() if not in release mode */
#ifndef NDEBUG
#define DEBUG(x)    x
#else
#define DEBUG(x)
#endif

#endif  // DEBUG_H_
