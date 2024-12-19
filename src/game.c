#include "snake.h"

void	spawn_snake(t_grid grid, t_snake_part *head_snake);
void	move_snake(int *snake_cooldown, t_snake_part *head_snake);
void	do_collision(t_grid grid, t_user_data *player1, t_user_data *player2);
void	generate_apple(t_grid *grid, int *apple_cooldown);
void	generate_object(t_grid *grid, int *object_cooldown);

void	print_grid(t_grid grid, t_gametick gametick)
{

}
void	print_snake(t_grid grid, t_snake_part *head_snake);

void	do_input(t_user_data *player1, t_user_data *player2)
{
	(void) player1;
	(void) player2;
	SDL_Event	event;
	
	while (SDL_PollEvent(&event))
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

void	init_gametick(t_gametick *gametick)
{
	gametick->elapsed_time = 0;
	gametick->apple_cooldown = APPLE_GENERATION_TIME;
	gametick->object_cooldown = OBJECT_GENERATION_TIME;
	gametick->snake_1_cooldown = SNAKE_MOVE_TIME;
	gametick->snake_2_cooldown = SNAKE_MOVE_TIME;
}

void	update_gametick(t_gametick *gametick, int speed1, int speed2)
{
	int	elapsed_time;

	elapsed_time = SDL_GetTicks();
	gametick->elapsed_time = elapsed_time - gametick->elapsed_time;
	gametick->apple_cooldown -= gametick->elapsed_time;
	gametick->object_cooldown -= gametick->elapsed_time;
	gametick->snake_1_cooldown -= gametick->elapsed_time * speed1;
	gametick->snake_2_cooldown -= gametick->elapsed_time * speed2;
}

void	print_scoreboard(SDL_Rect rect_pos, t_user_data player1, t_user_data player2)
{
	if(SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
		SDL_ExitWithError("print_scoreboard : color in white");

	if(SDL_RenderDrawRect(App.renderer, &rect_pos))
		SDL_ExitWithError("print_scoreboard : draw rect");

	rect_pos.y += SCOREBOARD_HEIGHT / 2 - get_text_height("A", App.font) / 2;
	SDL_Rect player_text_rect ={rect_pos.x + 20, rect_pos.y, get_text_width("Player", App.font), get_text_height("Player", App.font)};
	SDL_Rect score_text_rect = {rect_pos.x + 120 + get_text_width("A", App.font), rect_pos.y, get_text_width("score", App.font), get_text_height("score", App.font)};
	SDL_Rect life_text_rect ={rect_pos.x + 220 + get_text_width("A", App.font) + get_text_width("99999", App.font), rect_pos.y, get_text_width("life", App.font), get_text_height("life", App.font)};

	SDL_Rect id_rect_player1 = {player_text_rect.x + get_text_width("Player", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player1.id), App.font), get_text_height(ft_itoa(player1.id), App.font)};
	SDL_Rect score_rect_player1 = {score_text_rect.x + get_text_width("score", App.font) + 5, rect_pos.y,  get_text_width(ft_itoa(player1.score), App.font), get_text_height(ft_itoa(player1.score), App.font)};
	SDL_Rect life_rect_player1 = {life_text_rect.x + get_text_width("life", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player1.life), App.font), get_text_height(ft_itoa(player1.life), App.font)};


	render_text(App.renderer, "Player", player_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "score", score_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "life", life_text_rect, App.font, (SDL_Color){255, 255, 255, 255});

	render_text(App.renderer, ft_itoa(player1.id), id_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player1.score), score_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player1.life), life_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});

	player_text_rect.x = SCREEN_WIDTH - 20 - get_text_width("Player", App.font) - get_text_width("A", App.font);
	score_text_rect.x = SCREEN_WIDTH - 120 - get_text_width("score", App.font) - get_text_width("99999", App.font);
	life_text_rect.x = SCREEN_WIDTH - 220  - get_text_width("life", App.font) - get_text_width("A", App.font) - get_text_width("99999", App.font);

	SDL_Rect id_rect_player2 = {player_text_rect.x + get_text_width("Player", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player2.id), App.font), get_text_height(ft_itoa(player2.id), App.font)};
	SDL_Rect score_rect_player2 = {score_text_rect.x + get_text_width("score", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player2.score), App.font), get_text_height(ft_itoa(player2.score), App.font)};
	SDL_Rect life_rect_player2 = {life_text_rect.x + get_text_width("life", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player2.life), App.font), get_text_height(ft_itoa(player2.life), App.font)};

	render_text(App.renderer, "Player", player_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "score", score_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "life", life_text_rect, App.font, (SDL_Color){255, 255, 255, 255});

	render_text(App.renderer, ft_itoa(player2.id), id_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player2.score), score_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player2.life), life_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
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
			grid->cells[x][y].texture = YELLOW;
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
	init_gametick(&gametick);
	while (App.running && player1.life && player2.life)
	{
		update_gametick(&gametick, player1.head_snake->speed, player2.head_snake->speed);
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
