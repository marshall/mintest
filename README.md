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
        int main(int argc, char **argv) {
            mt_main(all_tests);
            return mt_fail_count;
        }

## Configuration

mintest supports a few preprocessor defines to configure the way test results are
reported

* `MT_OUT_FORMAT`: mintest reporting format. value: `MT_OUT_HUMAN` (default) or `MT_OUT_JSON`
* `MT_NL`: mintest newline character. default: `"\n"`
* `MT_PRINTF`: function used to print results. default: `printf`

## Building

To build and run the mintest self-tests, simply use the bundled `waf` build script:

        $ ./waf configure build test

## JSON output

When `MT_OUT_FORMAT` is defined to `MT_OUT_JSON`, mintest will output a JSON
parser friendly format. Due to the focus on simplicity and minimal footprint,
this output format is fairly simple.

Here is a prettified example from the JSON self-test:

        {
            "failures":[{
                    "test": "assert_msg_fail",
                    "message": "../tests/test_json.c:19: should_fail"
                },{
                    "test": "assert_fail",
                    "message": "../tests/test_json.c:31: ../tests/test_json.c:31: 0 == 1"
                },{
                    "test": "failed",
                    "message": "../tests/test_json.c:37: fail_msg"
                }],
            "passed": 2,
            "failed": 3,
            "total": 5
        }

## More examples
For more examples and tests, see the [tests](tests) directory.
