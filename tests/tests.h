#ifndef TESTS_H
# define TESTS_H

# include <stdio.h>
# include <stdlib.h>

# undef assert
# define assert(condition)    \
	do                       \
	{                        \
		if (!(condition))    \
		{                    \
			assert_file = 0; \
			fprintf(stderr, "Assertion failed at %s:%d\n", __FILE__, __LINE__); \
		}                    \
	} while (0)

void test_init_players(void);
void test_init_map(void);
void test_kill_app(void);
void test_init_app(void);
void test_init_gametick(void);
void test_update_gametick(void);

#endif
