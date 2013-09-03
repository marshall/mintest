/**
 * mintest - a minimal C unit testing framework, inspired by minunit
 *
 * Copyright 2013, Marshall Culpepper
 * Licensed under the Apache License, Version 2.0
 */
#include "mintest.h"
#include <string.h>

mt_test(assert_msg_pass)
{
    mt_assert_msg("custom_msg", 0 == 0);
    return 0;
}

mt_test(assert_msg_fail)
{
    mt_assert_msg("fail_msg", 0 == 1);
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

mt_test(fail)
{
    mt_fail("I fail");
    return 0;
}

mt_test(test_asserts)
{
    mt_assert(assert_msg_pass() == 0);
    mt_assert(strnstr(assert_msg_fail(), "fail_msg", 128) != NULL);
    mt_assert(assert_pass() == 0);
    mt_assert(assert_fail() != 0);
    mt_assert(strnstr(fail(), "I fail", 128) != NULL);
    return 0;
}

static void all_tests()
{
    mt_run_test(test_asserts);
}

int main(int argc, char **argv)
{
    mt_main(all_tests);
    return mt_fail_count;
}
