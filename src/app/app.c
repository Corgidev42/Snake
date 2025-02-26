#include "snake_together.h"

// Ce module centralisera l’initialisation de SDL, TTF,
// la gestion de la fenêtre,
// du rendu et le chargement des ressources graphiques.

// ----------- Fonctions d’initialisation générale ------------

void	init_app(void)
{
	srand(time(NULL));
	App.seed.number = rand();
	printf("Seed : %d\n", App.seed.number);
	init_seed(&App.seed);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		SDL_ExitWithError("Initialisation of SDL");
	App.window = SDL_CreateWindow("Snake EnV Numeric.", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_ALWAYS_ON_TOP);
	if (!App.window)
		SDL_ExitWithError("Create Window");
	App.renderer = SDL_CreateRenderer(App.window, -1, SDL_RENDERER_SOFTWARE);
	if (!App.renderer)
		SDL_ExitWithError("Create Renderer");
	App.running = SDL_TRUE;
	if (TTF_Init())
		SDL_ExitWithError("Initialisation of TTF");
	App.font = TTF_OpenFont("asset/kenney_mini.ttf", 16);
	if (!App.font)
		SDL_ExitWithError("Failed to load font");
	init_texture_rects();
	App.spritesheet_texture = load_texture("asset/spritesheet.png");
	App.available_bonus[0] = LIFE_UP;
	App.available_bonus[1] = TP;
	App.available_bonus[2] = STAR;
	App.available_bonus[3] = SLOW;
	App.nb_bonus = 4;
}

void	kill_app(void)
{
	TTF_CloseFont(App.font);
	TTF_Quit();
	SDL_DestroyTexture(App.spritesheet_texture);
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

// ----------- Chargement des textures et polices ------------

static void	init_texture_rects_color(t_color color)
{
	int	color_y_start;

	color_y_start = color * SPRITE_HEIGHT * 7;
	// Tile rects
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			App.texture_rects.tile[color][x + y * 4].x = x * SPRITE_WIDTH;
			App.texture_rects.tile[color][x + y * 4].y = color_y_start + y
				* SPRITE_HEIGHT;
			App.texture_rects.tile[color][x + y * 4].w = SPRITE_WIDTH;
			App.texture_rects.tile[color][x + y * 4].h = SPRITE_HEIGHT;
		}
	}
	// Obstacle rects
	for (int x = 0; x < 12; x++)
	{
		App.texture_rects.obstacle[color][x].x = (SPRITE_WIDTH * 4) + x
			* SPRITE_WIDTH;
		App.texture_rects.obstacle[color][x].y = color_y_start;
		App.texture_rects.obstacle[color][x].w = SPRITE_WIDTH;
		App.texture_rects.obstacle[color][x].h = SPRITE_HEIGHT * 2;
	}
	// Snake body rects
	for (int x = 0; x < 10; x++)
	{
		App.texture_rects.snake_body[color][x].x = x * SPRITE_WIDTH;
		App.texture_rects.snake_body[color][x].y = color_y_start + SPRITE_HEIGHT
			* 2;
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
				App.texture_rects.snake_head[color][y][z][x].x = y * (8
						* SPRITE_WIDTH) + x * SPRITE_WIDTH;
				App.texture_rects.snake_head[color][y][z][x].y = color_y_start
					+ SPRITE_HEIGHT * (3 + z);
				App.texture_rects.snake_head[color][y][z][x].w = SPRITE_WIDTH;
				App.texture_rects.snake_head[color][y][z][x].h = SPRITE_HEIGHT;
			}
		}
	}
}

static void	init_texture_rects(void)
{
	init_texture_rects_color(YELLOW);
	init_texture_rects_color(BLUE);
	init_texture_rects_color(GREEN);
	// Apple rects
	for (int x = 0; x < 3; x++)
	{
		App.texture_rects.apple[x].x = x * SPRITE_WIDTH;
		App.texture_rects.apple[x].y = SPRITE_HEIGHT * 21;
		App.texture_rects.apple[x].w = SPRITE_WIDTH;
		App.texture_rects.apple[x].h = SPRITE_HEIGHT;
	}
	// Bomb rects
	App.texture_bomb.r.x = 0;
	App.texture_bomb.r.y = 0;
	App.texture_bomb.r.w = SPRITE_WIDTH;
	App.texture_bomb.r.h = SPRITE_HEIGHT;
	App.texture_bomb.a1 = load_texture("asset/bomb/bomb1.png");
	App.texture_bomb.a2 = load_texture("asset/bomb/bomb2.png");
	App.texture_bomb.a3 = load_texture("asset/bomb/bomb3.png");
	// Bonus rects
	App.texture_bonus.r.x = 0;
	App.texture_bonus.r.y = 0;
	App.texture_bonus.r.w = SPRITE_WIDTH;
	App.texture_bonus.r.h = SPRITE_HEIGHT;
	App.texture_bonus.life_up = load_texture("asset/bonus/life_up.png");
	App.texture_bonus.tp = load_texture("asset/bonus/tp.png");
	App.texture_bonus.star = load_texture("asset/bonus/star.png");
	App.texture_bonus.slow = load_texture("asset/bonus/slow.png");
	// Cross texture
	App.texture_cross = load_texture("asset/cross.png");
}
// ----------- Variables globales ou structure centrale ------------
