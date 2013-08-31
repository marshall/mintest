/**
 * mintest - a minimal C unit testing framework, inspired by minunit
 *
 * Copyright 2013, Marshall Culpepper
 * Licensed under the Apache License, Version 2.0
 */

#ifndef MINTEST_H
#define MINTEST_H

#if !defined(MT_NL)
#define MT_NL "\n"
#endif // !defined(MT_NL)

#define MT_OUT_HUMAN 0
#define MT_OUT_JSON  1

#if !defined(MT_OUT_FORMAT)
#define MT_OUT_FORMAT MT_OUT_HUMAN
#endif // !defined(MT_OUT_FORMAT)

#if !defined(mt_printf)
#include <stdio.h>
#define mt_printf printf
#endif // !defined(mt_printf)

#define __str(s) #s
#define mt_str(s) __str(s)

#define mt_assert_msg(message, test) do { if (!(test)) return message; } while (0)
#define mt_assert(test) mt_assert_msg(__FILE__ ":" mt_str(__LINE__) ": " mt_str(test), test)
#define mt_fail(message) return __FILE__ ":" mt_str(__LINE__) ": " message

#if MT_OUT_FORMAT == MT_OUT_HUMAN

#define mt_report_begin()
#define mt_report_suite_begin(suite) mt_printf("Running " mt_str(suite) ".." MT_NL);
#define mt_report_test_begin(test)
#define mt_report_test_end(test)
#define mt_report_suite_end(suite)
#define mt_report_end()

#define mt_report_fail(test, message) mt_printf("FAIL  : " #test ": %s" MT_NL, message)
#define mt_report_passed() mt_printf("PASSED: %d" MT_NL, mt_pass_count)
#define mt_report_failed() mt_printf("FAILED: %d" MT_NL, mt_fail_count)
#define mt_report_total() mt_printf("TOTAL : %d" MT_NL, mt_tests_run)

#elif MT_OUT_FORMAT == MT_OUT_JSON

#define mt_report_begin() mt_printf("{\"suites\":" MT_NL);
#define mt_report_suite_begin(suite) mt_printf("\"" mt_str(suite) "\": [" MT_NL);
#define mt_report_test_begin(test) mt_printf("{\"name\": \"" mt_str(test) "\", \"fails\":[" MT_NL);
#define mt_report_test_end(test) mt_printf("null]}" MT_NL);
#define mt_report_suite_end(suite) mt_printf("]," MT_NL);
#define mt_report_end() mt_printf("null}" MT_NL);

#define mt_report_fail(test, message) mt_printf("\"%s\"," MT_NL, message)
#define mt_report_passed() mt_printf("\"passed\": %d," MT_NL, mt_pass_count)
#define mt_report_failed() mt_printf("\"failed\": %d," MT_NL, mt_fail_count)
#define mt_report_total() mt_printf("\"total\": %d" MT_NL, mt_tests_run)

#endif // MT_OUT_FORMAT

#define mt_run_suite(suite) do { \
    mt_report_suite_begin(suite); \
    suite(); \
    mt_report_suite_end(suite); \
} while (0)

#define mt_run_test(test) do { \
    mt_report_test_begin(test); \
    char *message = test(); \
    mt_tests_run++; \
    if (message) { \
        mt_fail_count++; \
        mt_report_fail(test, message); \
    } else { \
        mt_pass_count++; \
    } \
    mt_report_test_end(test); \
} while (0)

#define mt_test(name) static char *name()

#define mt_main(suite) do { \
    mt_report_begin(); \
    mt_run_suite(suite); \
    mt_report_passed(); \
    if (mt_fail_count > 0) { \
        mt_report_failed(); \
    } \
    mt_report_total(); \
    mt_report_end(); \
} while(0)

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

typedef void (*mt_suite)(void);

extern int mt_tests_run;
extern int mt_fail_count;
extern int mt_pass_count;

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

#endif
