# mintest
a minimal C unit testing framework targetted at embedded systems

## Installation

Copy include/mintest.h and src/mintest.c into your project, and start writing
tests.

## Example

        #include "mintest.h"

        mt_test(test1) {
            mt_assert(1 == 1);
            return 0;
        }
        mt_test(test2) {
            mt_fail("I fail");
            return 0;
        }
        void suite1() {
            mt_run_test(test1);
        }
        void suite2() {
            mt_run_test(test2):
        }
        void all_tests() {
            mt_run_suite(suite1);
            mt_run_suite(suite2);
        }
        int main(void) {
            mt_main(all_tests);
            return mt_fail_count;
        }

## JSON Output

By default, mintest prints human readable output. To enable JSON output, define
`MT_OUT_FORMAT` to `MT_OUT_JSON` before including `mintest.h`

## Custom printf

If your environment doesn't support printf, you can override this dependency by
defining `mt_printf` before including `mintest.h`
