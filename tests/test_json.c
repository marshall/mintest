/**
 * mintest - a minimal C unit testing framework, inspired by minunit
 *
 * Copyright 2013, Marshall Culpepper
 * Licensed under the Apache License, Version 2.0
 */

#define MT_OUT_FORMAT MT_OUT_JSON
#include "mintest.h"

mt_test(assert_msg_pass)
{
    mt_assert_msg("should_pass", 0 == 0);
    return 0;
}

mt_test(assert_msg_fail)
{
    mt_assert_msg("should_fail", 0 == 1);
    return 0;
}

mt_test(assert_pass)
{
    mt_assert(0 == 0);
    return 0;
}

mt_test(assert_fail)
{
    mt_assert(0 == 1);
    return 0;
}

mt_test(failed)
{
    mt_fail("fail_msg");
    return 0;
}

static void suite1()
{
    mt_run_test(assert_msg_pass);
    mt_run_test(assert_msg_fail);
    mt_run_test(assert_pass);
}

static void suite2()
{
    mt_run_test(assert_fail);
    mt_run_test(failed);
}

static void all_tests()
{
    mt_run_suite(suite1);
    mt_run_suite(suite2);
}

int main(int argc, char **argv)
{
    mt_main(all_tests);
    return mt_fail_count;
}
