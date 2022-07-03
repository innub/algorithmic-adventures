#ifndef TEST_HELPER
#define TEST_HELPER

#include <stdio.h>
#include <string.h>

#define RUN_TESTS_FLAG_LONG "--test"
#define RUN_TESTS_FLAG_SHORT "-t"

#define print_test_func_name() printf("===== %s =====\n", __func__)

#define passed() printf("PASSED\n");

static inline int has_test_flag(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        const char* arg = argv[i];
        if (strcmp(arg, RUN_TESTS_FLAG_LONG) == 0 || strcmp(arg, RUN_TESTS_FLAG_SHORT) == 0) {
            return 1;
        }
    }
    return 0;
}

#endif