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

#if !defined(MT_PRINTF)
#include <stdio.h>
#define mt_printf printf
#else
#define mt_printf MT_PRINTF
#endif // !defined(MT_PRINTF)

#define __str(s) #s
#define mt_str(s) __str(s)

#define mt_msg(message) __FILE__ ":" mt_str(__LINE__) ": " message
#define mt_assert_msg(message, test) do { if (!(test)) return mt_msg(message); } while (0)
#define mt_assert(test) mt_assert_msg(mt_msg(mt_str(test)), test)
#define mt_fail(message) return mt_msg(message)

#if MT_OUT_FORMAT == MT_OUT_HUMAN

#define mt_report_begin()
#define mt_report_suite_begin(suite) mt_printf("mintest: " mt_str(suite) ":" MT_NL);
#define mt_report_test_begin(test) mt_printf("mintest:     Running " mt_str(test) ".." MT_NL);
#define mt_report_test_end(test)
#define mt_report_suite_end(suite)
#define mt_report_end()

#define mt_report_fail(test, message) mt_printf("mintest: FAIL  : " #test ": %s" MT_NL, message)
#define mt_report_counts() \
    mt_printf("mintest: %d passed, %d failed, %d total" MT_NL, mt_pass_count, \
              mt_fail_count, mt_tests_run)


#elif MT_OUT_FORMAT == MT_OUT_JSON

#define mt_report_begin() mt_printf("{\"failures\":[");
#define mt_report_suite_begin(suite)
#define mt_report_test_begin(test)
#define mt_report_test_end(test)
#define mt_report_suite_end(suite)

#define mt_report_fail(test, message) \
    mt_printf("%s{\"test\":\"%s\",\"message\":\"%s\"}", \
              mt_fail_count > 1 ? "," : "", \
              mt_str(test), \
              message)

#define mt_report_counts() \
    mt_printf("], \"passed\": %d,\"failed\":%d,\"total\":%d", mt_pass_count, \
              mt_fail_count, mt_tests_run)

#define mt_report_end() mt_printf("}" MT_NL);

#else

#warn Unsupported mintest output format

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
    mt_report_counts(); \
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
