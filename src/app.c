#include "../include/app.h"
#include "../include/structs.h"

void	SDL_ExitWithError(const char *message)
{
	SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void	init_app(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		SDL_ExitWithError("Initialisation of SDL");
	App.window = SDL_CreateWindow("Snake EnV Numeric.", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH,
			SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_ALWAYS_ON_TOP);
	if (!App.window)
		SDL_ExitWithError("Create Window");
	App.renderer = SDL_CreateRenderer(App.window, -1, SDL_RENDERER_SOFTWARE);
	if (!App.renderer)
		SDL_ExitWithError("Create Renderer");
	App.running = SDL_TRUE;
}

void	kill_app(void)
{
	SDL_DestroyRenderer(App.renderer);
	SDL_DestroyWindow(App.window);
	SDL_Quit();
}
