#include <assert.h>
#include "app.h"
#include "tests.h"

t_app App;

void test_init_app(void)
{
	int assert_file = 1;
	// Initialize the app
	init_app();

	// Check if the window is created
	assert(App.window != NULL);

	// Check if the renderer is created
	assert(App.renderer != NULL);

	// Check if the app is running
	assert(App.running == SDL_TRUE);

	// Clean up
	kill_app();
	// Affiche le résultat du test si tout est correct
	printf( __FILE__ " / init_app() %s\033[0m\n", assert_file ? "\033[32m[OK]" : "\033[31m[KO]");
}

void test_kill_app(void)
{
	int assert_file = 1;
	// Initialize the app
	init_app();

	// Kill the app
	kill_app();

	// Check if SDL is quit
	assert(SDL_WasInit(SDL_INIT_EVERYTHING) == 0);

	// Affiche le résultat du test si tout est correct
	printf( __FILE__ " / kill_app() %s\033[0m\n", assert_file ? "\033[32m[OK]" : "\033[31m[KO]");
}

