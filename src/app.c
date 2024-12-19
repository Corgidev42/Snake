#include "snake.h"

static void	init_texture_rects_color(t_color color)
{
	int	color_y_start = color * SPRITE_HEIGHT * 7;

	// Tile rects
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			App.texture_rects.tile[color][x + y * 4].x = x * SPRITE_WIDTH;
			App.texture_rects.tile[color][x + y * 4].y = color_y_start + y * SPRITE_HEIGHT;
			App.texture_rects.tile[color][x + y * 4].w = SPRITE_WIDTH;
			App.texture_rects.tile[color][x + y * 4].h = SPRITE_HEIGHT;
		}
	}
	// Obstacle rects
	for (int x = 4; x < 16; x++)
	{
		App.texture_rects.obstacle[color][x].x = x * SPRITE_WIDTH;
		App.texture_rects.obstacle[color][x].y = color_y_start;
		App.texture_rects.obstacle[color][x].w = SPRITE_WIDTH;
		App.texture_rects.obstacle[color][x].h = SPRITE_HEIGHT * 2;
	}
	// Snake body rects
	for (int x = 0; x < 10; x++)
	{
		App.texture_rects.snake_body[color][x].x = x * SPRITE_WIDTH;
		App.texture_rects.snake_body[color][x].y = color_y_start + SPRITE_HEIGHT * 2;
		App.texture_rects.snake_body[color][x].w = SPRITE_WIDTH;
		App.texture_rects.snake_body[color][x].h = SPRITE_HEIGHT;
	}
	// Snake head rects
	for (int y = 0; y < NB_SNAKE_STATES; y++)
	{
		for (int z = 0; z < NB_ORIENTATIONS; z++)
		{
			for (int x = 0; x < 8; x++)
			{
				App.texture_rects.snake_head[color][y][z][x].x = x * SPRITE_WIDTH;
				App.texture_rects.snake_head[color][y][z][x].y = color_y_start + SPRITE_HEIGHT * (3 + y * 2 + z);
				App.texture_rects.snake_head[color][y][z][x].w = SPRITE_WIDTH;
				App.texture_rects.snake_head[color][y][z][x].h = SPRITE_HEIGHT;
			}
		}
	}
}

static void	init_texture_rects()
{
	init_texture_rects_color(YELLOW);
	init_texture_rects_color(BLUE);
	init_texture_rects_color(GREEN);
	// Apple rects
	for (int x = 0; x < 3; x++)
	{
		App.texture_rects.apple[x].x = x * SPRITE_WIDTH;
		App.texture_rects.apple[x].y = SPRITE_HEIGHT * 7;
		App.texture_rects.apple[x].w = SPRITE_WIDTH;
		App.texture_rects.apple[x].h = SPRITE_HEIGHT;
	}
}

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
	init_texture_rects();
	App.spritesheet_texture = load_texture("asset/spritesheet.png");
}
