#include "app.h"
#include "defs.h"
#include "structs.h"

void	spawn_snake(t_grid grid, t_snake_part *head_snake);
void	init_gametick(t_gametick *gametick);

void	do_input(t_user_data *player1, t_user_data *player2)
{
	(void) player1;
	(void) player2;
	SDL_Event	event;
	int			nb_events;

	nb_events = 0;
	while (!nb_events && SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				App.running = SDL_FALSE;
				break;
			default:
				break;
		}
	}
}

void	move_snake(int *snake_cooldown, t_snake_part *head_snake);
void	do_collision(t_grid grid, t_user_data *player1, t_user_data *player2);
void	update_gametick(t_gametick *gametick);
void	generate_apple(t_grid *grid, int *apple_cooldown);
void	generate_object(t_grid *grid, int *object_cooldown);
void	print_grid(t_grid grid, t_gametick gametick);
void	print_snake(t_grid grid, t_snake_part *head_snake);

void render_text(SDL_Renderer* renderer, const char* text, SDL_Rect rect, TTF_Font* font, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	if (!surface)
		SDL_ExitWithError("Failed to creation of surface");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		SDL_ExitWithError("Failed to creation of texture");
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}

void	print_scoreboard(SDL_Rect rect_pos, t_user_data player1, t_user_data player2)
{
	if(SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
		SDL_ExitWithError("print_scoreboard : color in white");

	if(SDL_RenderDrawRect(App.renderer, &rect_pos))
		SDL_ExitWithError("print_scoreboard : draw rect");

	SDL_Rect name_rect_player1 = {rect_pos.x, rect_pos.y + 20, 100, SCOREBOARD_HEIGHT / 2};
	SDL_Rect name_rect_player2 = {rect_pos.x + SCREEN_WIDTH - 50, rect_pos.y + 20, 100, SCOREBOARD_HEIGHT / 2};

	SDL_Rect life_rect_player1 = {rect_pos.x + 200, rect_pos.y + 20, 32, SCOREBOARD_HEIGHT / 2};
	SDL_Rect life_rect_player2 = {rect_pos.x + SCREEN_WIDTH - 200, rect_pos.y + 20, 32, SCOREBOARD_HEIGHT / 2};

	SDL_Rect score_rect_player1 = {rect_pos.x + 400, rect_pos.y + 20, 100, SCOREBOARD_HEIGHT / 2};
	SDL_Rect score_rect_player2 = {rect_pos.x + SCREEN_WIDTH - 400, rect_pos.y + 20, 100, SCOREBOARD_HEIGHT / 2};



	render_text(App.renderer, "Player 1", name_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "3", life_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "1013", score_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "Player 2", name_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "3", life_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "4343", score_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
}

void	free_all_game(t_grid grid)
{
	int	x;

	x = 0;
	while (x < GRID_COLS)
	{
		free(grid.cells[x]);
		x++;
	}
	free(grid.cells);
}

void	init_map(t_grid *grid)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	grid->rect_pos.x = GRID_POS_X ; grid->rect_pos.y = GRID_POS_Y ; grid->rect_pos.w = GRID_WIDTH ; grid ->rect_pos.h = GRID_HEIGHT;

	grid->cells = malloc(sizeof(t_cell* ) * GRID_COLS);
	while (x < GRID_COLS)
	{
		grid->cells[x] = malloc(sizeof(t_cell) * GRID_COLS);
		y = 0;
		while (y < GRID_ROWS)
		{
			grid->cells[x][y].coords.x = x;
			grid->cells[x][y].coords.y = y;
			if (x == 0 || y == 0 || x == GRID_COLS - 1 || y == GRID_ROWS - 1)
				grid->cells[x][y].obstacle = 1;
			else
				grid->cells[x][y].obstacle = 0;
			grid->cells[x][y].has_apple = SDL_FALSE;
			grid->cells[x][y].has_bomb = SDL_FALSE;
			grid->cells[x][y].bonus = BONUS_EMPTY;
			grid->cells[x][y].texture = EMPTY;
			grid->cells[x][y].is_pending = SDL_FALSE;
			y++;
		}
		x++;
	}
}

void	game_window(t_user_data player1, t_user_data player2)
{
	t_grid		grid;
	t_gametick	gametick;
	SDL_Rect	scoreboard_rect_pos;

	scoreboard_rect_pos.x = SCOREBOARD_POS_X; scoreboard_rect_pos.y = SCOREBOARD_POS_Y; scoreboard_rect_pos.h = SCOREBOARD_HEIGHT ; scoreboard_rect_pos.w = SCOREBOARD_WIDTH;
	init_map(&grid);
	// spawn_snake(grid, player1.head_snake);
	// spawn_snake(grid, player2.head_snake);
	// init_gametick(&gametick);
	while (App.running && player1.life && player2.life)
	{
		// update_gametick(&gametick);
		if(SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255))
			SDL_ExitWithError("Color set in black");
		if(SDL_RenderClear(App.renderer))
			SDL_ExitWithError("Render clear");

		do_input(&player1, &player2);

		// move_snake(&gametick.snake_1_cooldown, player1.head_snake);
		// move_snake(&gametick.snake_2_cooldown, player2.head_snake);

		// do_collision(grid, &player1, &player2);

		// generate_apple(&grid, &gametick.apple_cooldown);
		// generate_object(&grid,&gametick.object_cooldown);

		//print_grid(grid, gametick);
		// print_snake(grid, player1.head_snake);
		// print_snake(grid, player2.head_snake);

		print_scoreboard(scoreboard_rect_pos, player1, player2);

		SDL_RenderPresent(App.renderer);
	}
	free_all_game(grid);
}
