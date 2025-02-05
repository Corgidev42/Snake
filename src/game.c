#include "snake.h"

void	do_collision(t_grid grid, t_user_data *player1, t_user_data *player2);

void	generate_object(t_grid *grid, int *object_cooldown);

int		get_seed_number(int x, int y, int max)
{
	return ((x + y) % max);
}

void	move_snake(int *snake_cooldown, t_user_data *player)
{
	t_snake_part *current;
	t_snake_part *prev;

	prev = player->head_snake;
	current = player->head_snake;
	if (*snake_cooldown > 0)
		return ;
	if (*snake_cooldown <= 0)
	{
		while(current)
		{
			prev = current;
			current = prev->next;
			if (current->next == NULL)
			{
				current->next = player->head_snake;
				prev->next = NULL;

				current->coords.x = player->head_snake->coords.x;
				current->coords.y = player->head_snake->coords.y;
				current->orientation = player->orientation_snake;
				player->head_snake = current;
				break;
			}
		}
		current = player->head_snake->next;
		switch (player->orientation_snake)
		{
		case LEFT:
			player->head_snake->coords.x -= 1;
			if (current)
				current->orientation = LEFT;
			break;
		case RIGHT:
			player->head_snake->coords.x += 1;
			if (current)
				current->orientation = RIGHT;
			break;
		case UP:
			player->head_snake->coords.y -= 1;
			if (current)
				current->orientation = UP;
			break;
		case DOWN:
			player->head_snake->coords.y += 1;
			if (current)
				current->orientation = DOWN;
			break;
		default:
			break;
		}
		*snake_cooldown += SNAKE_MOVE_TIME;
	}
}

SDL_bool	cell_is_empty(t_cell *cell)
{
	if (cell->obstacle == OBS_EMPTY
		&& cell->has_apple == SDL_FALSE
		&& cell->has_bomb == SDL_FALSE
		&& cell->has_snake == SDL_FALSE
		&& cell->bonus == BONUS_EMPTY)
		return (SDL_TRUE);
	return (SDL_FALSE);
}

SDL_bool	recursive_neighbourg_empty_cells(t_grid *grid, int x, int y, int r, int i)
{
	SDL_bool	result = SDL_TRUE;

	if (!cell_is_empty(&grid->cells[x][y]))
		return (SDL_FALSE);
	if (i < r)
	{
		if (x > 0 && !recursive_neighbourg_empty_cells(grid, x - 1, y, r, i + 1))
			result = SDL_FALSE;
		if (x < GRID_COLS - 1 && !recursive_neighbourg_empty_cells(grid, x + 1, y, r, i + 1))
			result = SDL_FALSE;
		if (y > 0 && !recursive_neighbourg_empty_cells(grid, x, y - 1, r, i + 1))
			result = SDL_FALSE;
		if (y < GRID_ROWS - 1 && !recursive_neighbourg_empty_cells(grid, x, y + 1, r, i + 1))
			result = SDL_FALSE;
	}
	return (result);
}

t_cell	*get_rand_empty_cell(t_grid *grid, int r)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (SDL_TRUE)
	{
		x = rand() % GRID_COLS;
		y = rand() % GRID_ROWS;
		if (recursive_neighbourg_empty_cells(grid, x, y, r, 0))
			return (&grid->cells[x][y]);
	}
}

void	generate_apple(t_grid *grid, int *apple_cooldown)
{
	t_cell *cell;
	if (*apple_cooldown > 0)
		return;
	if (*apple_cooldown <= 0)
	{
		cell = get_rand_empty_cell(grid, 0);
		cell->has_apple = SDL_TRUE;
		*apple_cooldown += APPLE_GENERATION_TIME;
	}
}

void	spawn_snake(t_grid *grid, t_user_data *player)
{
	t_snake_part	*head_snake = player->head_snake;
	t_cell			*cell;

	cell = get_rand_empty_cell(grid, 2);
	head_snake->coords.x = cell->coords.x;
	head_snake->coords.y = cell->coords.y;
	head_snake->orientation = rand() % 4;
	player->orientation_snake = head_snake->orientation;
	head_snake->next = NULL;
	head_snake->speed = 1;
	add_behind_snake_part(head_snake);
	cell->has_snake = SDL_TRUE;
	grid->cells[head_snake->next->coords.x][head_snake->next->coords.y].has_snake = SDL_TRUE;
}

void	print_grid(t_grid grid, t_gametick gametick)
{
	int	x;
	int	y;
	SDL_Rect cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};

	x = 0;
	while (x < GRID_COLS)
	{
		y = 0;
		cell_rect.y = GRID_POS_Y;
		while (y < GRID_ROWS)
		{
			SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.tile[grid.cells[x][y].texture][get_seed_number(x, y, NB_TILES)], &cell_rect);

			if (grid.cells[x][y].has_apple == SDL_TRUE)
				SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.apple[get_seed_number(x, y, NB_APPLES)], &cell_rect);

			cell_rect.y += CELL_HEIGHT;
			y++;
		}
		cell_rect.x += CELL_WIDTH;
		x++;
	}
}

t_snake_part	*add_behind_snake_part(t_snake_part *head_snake)
{
	t_snake_part	*new_snake_part;
	t_snake_part	*current;

	new_snake_part = malloc(sizeof(t_snake_part));
	if (!new_snake_part)
		SDL_ExitWithError("malloc new_snake_part");
	new_snake_part->speed = head_snake->speed;
	new_snake_part->skin = head_snake->skin;
	new_snake_part->next = NULL;

	current = head_snake;
	while (current && current->next)
		current = current->next;
	new_snake_part->orientation = current->orientation;
	switch (current->orientation)
	{
	case UP:
		new_snake_part->coords.x = current->coords.x;
		new_snake_part->coords.y = current->coords.y + 1;
		break;
	case DOWN:
		new_snake_part->coords.x = current->coords.x;
		new_snake_part->coords.y = current->coords.y - 1;
		break;
	case LEFT:
		new_snake_part->coords.x = current->coords.x + 1;
		new_snake_part->coords.y = current->coords.y;
		break;
	case RIGHT:
		new_snake_part->coords.x = current->coords.x - 1;
		new_snake_part->coords.y = current->coords.y;
		break;
	default:
		break;
	}
	current->next = new_snake_part;
	return (new_snake_part);
}

void	print_snake(t_grid grid, t_snake_part *head_snake, int snake_animation)
{
	t_snake_part	*current;
	SDL_Rect		cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};

	current = head_snake;
	cell_rect.x = GRID_POS_X + CELL_WIDTH * current->coords.x;
	cell_rect.y = GRID_POS_Y + CELL_HEIGHT * current->coords.y;
	SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.snake_head[current->skin][NORMAL][current->orientation][snake_animation / (SNAKES_ANIMATION_TIME / 8)], &cell_rect);

	current = current->next;
	while (current)
	{
		cell_rect.x = GRID_POS_X + CELL_WIDTH * current->coords.x;
		cell_rect.y = GRID_POS_Y + CELL_HEIGHT * current->coords.y;
		int	body_sprite;
		if (current->next)
		{
			if ((current->orientation == UP && current->next->orientation == UP)
				|| (current->orientation == DOWN && current->next->orientation == DOWN))
				body_sprite = 0;
			if ((current->orientation == LEFT && current->next->orientation == LEFT)
				|| (current->orientation == RIGHT && current->next->orientation == RIGHT))
				body_sprite = 1;
			if ((current->orientation == UP && current->next->orientation == RIGHT)
				|| (current->orientation == LEFT && current->next->orientation == DOWN))
				body_sprite = 2;
			if ((current->orientation == UP && current->next->orientation == LEFT)
				|| (current->orientation == RIGHT && current->next->orientation == DOWN))
				body_sprite = 3;
			if ((current->orientation == LEFT && current->next->orientation == UP)
				|| (current->orientation == DOWN && current->next->orientation == RIGHT))
				body_sprite = 4;
			if ((current->orientation == RIGHT && current->next->orientation == UP)
				|| (current->orientation == DOWN && current->next->orientation == LEFT))
				body_sprite = 5;
		}
		else
			body_sprite = 6 + current->orientation;
		SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.snake_body[current->skin][body_sprite], &cell_rect);
		current = current->next;
	}
}


void	print_obstacles(t_grid grid)
{
	int	x;
	int	y;
	SDL_Rect cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};

	x = 0;
	while (x < GRID_COLS)
	{
		y = 0;
		cell_rect.y = GRID_POS_Y;
		while (y < GRID_ROWS)
		{
			if (grid.cells[x][y].obstacle == SDL_TRUE)
			{
				cell_rect.y -= CELL_HEIGHT;
				cell_rect.h += CELL_HEIGHT;
				SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.obstacle[grid.cells[x][y].texture][get_seed_number(x, y, NB_OBSTACLES)], &cell_rect);
				cell_rect.y += CELL_HEIGHT;
				cell_rect.h -= CELL_HEIGHT;
			}
			cell_rect.y += CELL_HEIGHT;
			y++;
		}
		cell_rect.x += CELL_WIDTH;
		x++;
	}
}

void	rotate_snake(t_user_data *player, t_orientation orientation)
{
	t_snake_part	*second = player->head_snake->next;

	if (second)
	{
		if (second->orientation == UP && orientation == DOWN)
			return;
		if (second->orientation == DOWN && orientation == UP)
			return;
		if (second->orientation == LEFT && orientation == RIGHT)
			return;
		if (second->orientation == RIGHT && orientation == LEFT)
			return;
	}
	player->orientation_snake = orientation;
}

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
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						App.running = SDL_FALSE;
						break;
					case SDL_SCANCODE_A:
						rotate_snake(player1, LEFT);
						break;
					case SDL_SCANCODE_D:
						rotate_snake(player1, RIGHT);
						break;
					case SDL_SCANCODE_W:
						rotate_snake(player1, UP);
						break;
					case SDL_SCANCODE_S:
						rotate_snake(player1, DOWN);
						break;
					case SDL_SCANCODE_LEFT:
						rotate_snake(player2, LEFT);
						break;
					case SDL_SCANCODE_RIGHT:
						rotate_snake(player2, RIGHT);
						break;
					case SDL_SCANCODE_UP:
						rotate_snake(player2, UP);
						break;
					case SDL_SCANCODE_DOWN:
						rotate_snake(player2, DOWN);
						break;
					default:
						break;
				}
				break;
		}
	}
}

void	init_gametick(t_gametick *gametick)
{
	gametick->elapsed_time = SDL_GetTicks();
	gametick->apple_cooldown = APPLE_GENERATION_TIME;
	gametick->object_cooldown = OBJECT_GENERATION_TIME;
	gametick->snake_1_cooldown = SNAKE_MOVE_TIME;
	gametick->snake_2_cooldown = SNAKE_MOVE_TIME;
	gametick->snakes_animation = SNAKES_ANIMATION_TIME;
}

void	update_gametick(t_gametick *gametick, int speed1, int speed2)
{
	int	elapsed_time = SDL_GetTicks() - gametick->elapsed_time;

	gametick->apple_cooldown -= elapsed_time;
	gametick->object_cooldown -= elapsed_time;
	gametick->snake_1_cooldown -= elapsed_time * speed1;
	gametick->snake_2_cooldown -= elapsed_time * speed2;
	gametick->snakes_animation -= elapsed_time;
	if (gametick->snakes_animation <= 0)
		gametick->snakes_animation += SNAKES_ANIMATION_TIME;
	gametick->elapsed_time = SDL_GetTicks();
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
			grid->cells[x][y].has_snake = SDL_FALSE;
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
	SDL_Rect scoreboard_rect_pos = {SCOREBOARD_POS_X, SCOREBOARD_POS_Y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT};
	SDL_Rect grid_rect_pos = {GRID_POS_X, GRID_POS_Y, GRID_WIDTH, GRID_HEIGHT};

	init_map(&grid);
	spawn_snake(&grid, &player1);
	spawn_snake(&grid, &player2);
	init_gametick(&gametick);
	while (App.running && player1.life && player2.life)
	{
		update_gametick(&gametick, player1.head_snake->speed, player2.head_snake->speed);
		if(SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255))
			SDL_ExitWithError("Color set in black");
		if(SDL_RenderClear(App.renderer))
			SDL_ExitWithError("Render clear");

		do_input(&player1, &player2);

		move_snake(&gametick.snake_1_cooldown, &player1);
		move_snake(&gametick.snake_2_cooldown, &player2);

		// do_collision(grid, &player1, &player2);

		generate_apple(&grid, &gametick.apple_cooldown);
		// generate_object(&grid,&gametick.object_cooldown);

		print_grid(grid, gametick);
		print_snake(grid, player1.head_snake, gametick.snakes_animation);
		print_snake(grid, player2.head_snake, gametick.snakes_animation);
		print_obstacles(grid);
		print_scoreboard(scoreboard_rect_pos, player1, player2);

		SDL_RenderPresent(App.renderer);

		SDL_Delay(1000 / 60);
	}
	free_all_game(grid);
}
