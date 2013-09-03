/**
 * mintest - a minimal C unit testing framework, inspired by minunit
 *
 * Copyright 2013, Marshall Culpepper
 * Licensed under the Apache License, Version 2.0
 */


#define MT_NL "[END]\r\n"
#include "mintest.h"

mt_test(fail)
{
    mt_fail("failure");
    return 0;
}

static void all_tests()
{
    mt_run_test(fail);
}

int main(int argc, char **argv)
{
    mt_main(all_tests);
    return mt_fail_count;
}
