/**
 * mintest - a minimal C unit testing framework, inspired by minunit
 *
 * Copyright 2013, Marshall Culpepper
 * Licensed under the Apache License, Version 2.0
 */

#define MT_ENABLE_TRACE
#include "mintest.h"

mt_test(trace)
{
    mt_assert("trace me");
    return 0;
}

static void all_tests()
{
    mt_run_test(trace);
}

int main(int argc, char **argv)
{
    mt_main(all_tests);
    return mt_fail_count;
}
