#include "mintest.h"

mt_test(assert_false)
{
    mt_assert(0 == 1);
    return 0;
}

mt_test(assert_true)
{
    mt_assert(0 == 0);
    return 0;
}

mt_test(failed)
{
    mt_fail("I failed");
    return 0;
}

mt_test(test_asserts)
{
    mt_assert(assert_true() == 0);
    mt_assert(assert_false() != 0);
    mt_assert(failed() != 0);
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
