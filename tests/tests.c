#include "tests.h"

int	main(int argc, char *argv[])
{
	test_init_app();
	test_kill_app();
	test_init_players();
	test_init_map();
	test_init_gametick();
	test_update_gametick();
	
	return (0);
}
