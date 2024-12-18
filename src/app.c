#include "structs.h"
#include "app.h"

void	kill_app(void)
{
	TTF_CloseFont(App.font);
	TTF_Quit();

	SDL_DestroyRenderer(App.renderer);
	SDL_DestroyWindow(App.window);
	SDL_Quit();
}

void	SDL_ExitWithError(const char *message)
{
	SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
	kill_app();
	exit(EXIT_FAILURE);
}

void	init_app(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		SDL_ExitWithError("Initialisation of SDL");
	App.window = SDL_CreateWindow("Snake EnV Numeric.", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP);
	if (!App.window)
		SDL_ExitWithError("Create Window");
	App.renderer = SDL_CreateRenderer(App.window, -1, SDL_RENDERER_SOFTWARE);
	if (!App.renderer)
		SDL_ExitWithError("Create Renderer");
	App.running = SDL_TRUE;
	if (TTF_Init())
		SDL_ExitWithError("Initialisation of TTF");
	App.font = TTF_OpenFont("asset/kenney_mini.ttf", 16);
	if(!App.font)
		SDL_ExitWithError("Failed to load font");
}
