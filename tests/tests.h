#ifndef TESTS_H
# define TESTS_H

#include <stdio.h>
#include <stdlib.h>

#undef assert
#define assert(condition)                                                        \
    do {                                                                         \
        if (!(condition)) {                                                      \
            assert_file = 0;                                                     \
            fprintf(stderr, "Assertion failed at %s:%d\n", __FILE__, __LINE__);  \
        }                                                                        \
    } while (0)

void test_init_players(void);

#endif