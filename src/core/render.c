#include "snake_together.h"

// ------- Rendu de la grille, obstacles, bonus -------
void	print_grid(t_grid grid)
{
	int			x;
	int			y;
	SDL_Rect	cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};
	int			is_light;
	SDL_Texture	*bonus_texture;

	x = 0;
	while (x < GRID_COLS)
	{
		y = 0;
		cell_rect.y = GRID_POS_Y;
		while (y < GRID_ROWS)
		{
			if (grid.cells[x][y].texture == YELLOW)
				is_light = App.seed.is_yellow_light;
			else if (grid.cells[x][y].texture == GREEN)
				is_light = App.seed.is_green_light;
			else
				is_light = App.seed.is_blue_light;
			SDL_RenderCopy(App.renderer, App.spritesheet_texture,
				&App.texture_rects.tile[grid.cells[x][y].texture][(is_light ? 0 : 4)
				+ (grid.cells[x][y].rand % 4)], &cell_rect);
			if (grid.cells[x][y].has_apple == SDL_TRUE)
				SDL_RenderCopy(App.renderer, App.spritesheet_texture,
					&App.texture_rects.apple[grid.cells[x][y].rand % 3],
					&cell_rect);
			if (grid.cells[x][y].has_bomb == SDL_TRUE)
				SDL_RenderCopy(App.renderer, App.texture_bomb.a3,
					&App.texture_bomb.r, &cell_rect);
			if (grid.cells[x][y].bonus != BONUS_EMPTY)
			{
				bonus_texture = NULL;
				switch (grid.cells[x][y].bonus)
				{
				case LIFE_UP:
					bonus_texture = App.texture_bonus.life_up;
					break ;
				case STAR:
					bonus_texture = App.texture_bonus.star;
					break ;
				case SLOW:
					bonus_texture = App.texture_bonus.slow;
					break ;
				case TP:
					bonus_texture = App.texture_bonus.tp;
					break ;
				default:
					break ;
				}
				SDL_RenderCopy(App.renderer, bonus_texture, NULL, &cell_rect);
			}
			cell_rect.y += CELL_HEIGHT;
			y++;
		}
		cell_rect.x += CELL_WIDTH;
		x++;
	}
}

void	print_obstacles(t_grid grid)
{
	int			x;
	int			y;
	SDL_Rect	cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};

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
				SDL_RenderCopy(App.renderer, App.spritesheet_texture,
					&App.texture_rects.obstacle[grid.cells[x][y].texture][grid.cells[x][y].rand
					% 12], &cell_rect);
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

void	print_is_pending(t_grid grid, int object_cooldown)
{
	SDL_Rect	cell_rect;
	SDL_Rect	text_rect;
	t_cell		*is_pending_cell;
	char		*cooldown_text;
	int			text_width;
	int			text_height;

	// Récupère la cellule en attente
	is_pending_cell = get_is_pending_cell(&grid);
	if (!is_pending_cell)
		return ;
	// Définition de la position de la cellule
	cell_rect.x = GRID_POS_X + CELL_WIDTH * is_pending_cell->coords.x;
	cell_rect.y = GRID_POS_Y + CELL_HEIGHT * is_pending_cell->coords.y;
	cell_rect.w = CELL_WIDTH;
	cell_rect.h = CELL_HEIGHT;
	// Convertit le cooldown en texte
	cooldown_text = ft_itoa((object_cooldown / 1000) + 1);
	// Calcule la taille du texte
	text_width = get_text_width(cooldown_text, App.font) * 2;
	text_height = get_text_height(cooldown_text, App.font) * 2;
	// Centre le texte dans la cellule
	text_rect.x = cell_rect.x + (cell_rect.w - text_width) / 2;
	text_rect.y = cell_rect.y + (cell_rect.h - text_height) / 2;
	text_rect.w = text_width;
	text_rect.h = text_height;
	// Affiche le texte centré
	render_text(App.renderer, cooldown_text, text_rect, App.font,
		(SDL_Color){255, 255, 255, 255});
	free(cooldown_text);
}

// ------- Rendu des serpents -------
void	print_snake(t_grid grid, t_snake_part *head_snake, int snake_animation)
{
	t_snake_part	*current;
	SDL_Rect		cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};
	int body_sprite;

	current = head_snake;
	cell_rect.x = GRID_POS_X + CELL_WIDTH * current->coords.x;
	cell_rect.y = GRID_POS_Y + CELL_HEIGHT * current->coords.y;
	SDL_RenderCopy(App.renderer, App.spritesheet_texture,
		&App.texture_rects.snake_head[current->skin][current->snake_state][current->orientation][snake_animation
		/ (SNAKES_ANIMATION_TIME / 8)], &cell_rect);
	current = current->next;
	while (current)
	{
		if (current->coords.x < 0 || current->coords.x >= GRID_COLS
			|| current->coords.y < 0 || current->coords.y >= GRID_ROWS)
			break ;
		cell_rect.x = GRID_POS_X + CELL_WIDTH * current->coords.x;
		cell_rect.y = GRID_POS_Y + CELL_HEIGHT * current->coords.y;
		if (current->next)
		{
			if ((current->orientation == UP && current->next->orientation == UP)
				|| (current->orientation == DOWN
					&& current->next->orientation == DOWN))
				body_sprite = 0;
			if ((current->orientation == LEFT
					&& current->next->orientation == LEFT)
				|| (current->orientation == RIGHT
					&& current->next->orientation == RIGHT))
				body_sprite = 1;
			if ((current->orientation == UP
					&& current->next->orientation == RIGHT)
				|| (current->orientation == LEFT
					&& current->next->orientation == DOWN))
				body_sprite = 2;
			if ((current->orientation == UP
					&& current->next->orientation == LEFT)
				|| (current->orientation == RIGHT
					&& current->next->orientation == DOWN))
				body_sprite = 3;
			if ((current->orientation == LEFT
					&& current->next->orientation == UP)
				|| (current->orientation == DOWN
					&& current->next->orientation == RIGHT))
				body_sprite = 4;
			if ((current->orientation == RIGHT
					&& current->next->orientation == UP)
				|| (current->orientation == DOWN
					&& current->next->orientation == LEFT))
				body_sprite = 5;
		}
		else
			body_sprite = 6 + current->orientation;
		SDL_RenderCopy(App.renderer, App.spritesheet_texture,
			&App.texture_rects.snake_body[current->skin][body_sprite],
			&cell_rect);
		current = current->next;
	}
}

// ------- Rendu de l’interface (scoreboard, jauges, actions) -------
void	print_actions(SDL_Rect rect_pos, t_user_data player1,
		t_user_data player2)
{
	SDL_Rect		speed_rect = {rect_pos.x + 20, rect_pos.y + 5, 50, 40};
	SDL_Rect 		first_rect = {0, 0, 40, 40};
	SDL_Rect 		second_rect = {0, 0, 30, 30};
	SDL_Texture		*bonus_texture;

	if (SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
		SDL_ExitWithError("print_actions : color in white");
	if (SDL_RenderDrawRect(App.renderer, &rect_pos))
		SDL_ExitWithError("print_actions : draw rect");
	// Print player 1 actions
	// Print player 1 speed -> jauge de vitesse en fonction de NB_APPLE_SPEED
	for (int i = 0; i < NB_APPLE_SPEED; i++)
	{
		int	color[4] = {0, 0, 0, 255};
		if (player1.nb_apple_speed > i)
		{
			if (player1.head_snake->skin == YELLOW)
			{
				color[0] = 255;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player1.head_snake->skin == GREEN)
			{
				color[0] = 0;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player1.head_snake->skin == BLUE)
			{
				color[0] = 0;
				color[1] = 0;
				color[2] = 255;
			}
		}
		if (SDL_SetRenderDrawColor(App.renderer, color[0], color[1], color[2],
				color[3]))
			SDL_ExitWithError("print_actions : color");
		if (SDL_RenderFillRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		if (SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
			SDL_ExitWithError("print_actions : color in white");
		if (SDL_RenderDrawRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		speed_rect.x += 50;
	}
	SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255);
	first_rect.x = speed_rect.x + 30;
	first_rect.y = speed_rect.y;
	second_rect.x = first_rect.x + first_rect.w + 10;
	second_rect.y = first_rect.y + 5;
	// Print player 1 bonuses
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (player1.inventory[i] != BONUS_EMPTY)
		{
			bonus_texture = NULL;
			switch (player1.inventory[i])
			{
			case LIFE_UP:
				bonus_texture = App.texture_bonus.life_up;
				break ;
			case STAR:
				bonus_texture = App.texture_bonus.star;
				break ;
			case SLOW:
				bonus_texture = App.texture_bonus.slow;
				break ;
			case TP:
				bonus_texture = App.texture_bonus.tp;
				break ;
			default:
				break ;
			}
			SDL_RenderCopy(App.renderer, bonus_texture, NULL,
				(i == 0 ? &first_rect : &second_rect));
		}
		SDL_RenderDrawRect(App.renderer, (i == 0 ? &first_rect : &second_rect));
	}
	// Print player 2 actions
	// Print player 2 speed -> jauge de vitesse en fonction de NB_APPLE_SPEED
	speed_rect.x = SCREEN_WIDTH - 20 - 50;
	speed_rect.y = rect_pos.y + 5;
	for (int i = 0; i < NB_APPLE_SPEED; i++)
	{
		int	color[4] = {0, 0, 0, 255};
		if (player2.nb_apple_speed > i)
		{
			if (player2.head_snake->skin == YELLOW)
			{
				color[0] = 255;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player2.head_snake->skin == GREEN)
			{
				color[0] = 0;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player2.head_snake->skin == BLUE)
			{
				color[0] = 0;
				color[1] = 0;
				color[2] = 255;
			}
		}
		if (SDL_SetRenderDrawColor(App.renderer, color[0], color[1], color[2],
				color[3]))
			SDL_ExitWithError("print_actions : color in black");
		if (SDL_RenderFillRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		if (SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
			SDL_ExitWithError("print_actions : color in black");
		if (SDL_RenderDrawRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		speed_rect.x -= 50;
	}
	SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255);
	// Print player 2 bonuses
	first_rect.x = speed_rect.x - 20;
	second_rect.x = first_rect.x - 40;
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (player2.inventory[i] != BONUS_EMPTY)
		{
			bonus_texture = NULL;
			switch (player2.inventory[i])
			{
			case LIFE_UP:
				bonus_texture = App.texture_bonus.life_up;
				break ;
			case STAR:
				bonus_texture = App.texture_bonus.star;
				break ;
			case SLOW:
				bonus_texture = App.texture_bonus.slow;
				break ;
			case TP:
				bonus_texture = App.texture_bonus.tp;
				break ;
			default:
				break ;
			}
			SDL_RenderCopy(App.renderer, bonus_texture, NULL,
				(i == 0 ? &first_rect : &second_rect));
		}
		SDL_RenderDrawRect(App.renderer, (i == 0 ? &first_rect : &second_rect));
	}
}

void	print_scoreboard(SDL_Rect rect_pos, t_user_data player1,
		t_user_data player2)
{
	SDL_Rect		player_text_rect = {rect_pos.x + 20, rect_pos.y, get_text_width("Player",
		App.font), get_text_height("Player", App.font)};
	SDL_Rect		score_text_rect = {rect_pos.x + 120 + get_text_width("A", App.font),
		rect_pos.y, get_text_width("score", App.font), get_text_height("score",
			App.font)};
	SDL_Rect		life_text_rect = {rect_pos.x + 220 + get_text_width("A", App.font)
		+ get_text_width("99999", App.font), rect_pos.y, get_text_width("life",
			App.font), get_text_height("life", App.font)};
	SDL_Rect		id_rect_player1 = {player_text_rect.x + get_text_width("Player", App.font)
		+ 5, rect_pos.y, get_text_width(ft_itoa(player1.id), App.font),
		get_text_height(ft_itoa(player1.id), App.font)};
	SDL_Rect		score_rect_player1 = {score_text_rect.x + get_text_width("score", App.font)
		+ 5, rect_pos.y, get_text_width(ft_itoa(player1.score), App.font),
		get_text_height(ft_itoa(player1.score), App.font)};
	SDL_Rect		life_rect_player1 = {life_text_rect.x + get_text_width("life", App.font)
		+ 5, rect_pos.y, get_text_width(ft_itoa(player1.life), App.font),
		get_text_height(ft_itoa(player1.life), App.font)};
	SDL_Rect		id_rect_player2 = {player_text_rect.x + get_text_width("Player", App.font)
		+ 5, rect_pos.y, get_text_width(ft_itoa(player2.id), App.font),
		get_text_height(ft_itoa(player2.id), App.font)};
	SDL_Rect		score_rect_player2 = {score_text_rect.x + get_text_width("score", App.font)
		+ 5, rect_pos.y, get_text_width(ft_itoa(player2.score), App.font),
		get_text_height(ft_itoa(player2.score), App.font)};
	SDL_Rect		life_rect_player2 = {life_text_rect.x + get_text_width("life", App.font)
		+ 5, rect_pos.y, get_text_width(ft_itoa(player2.life), App.font),
		get_text_height(ft_itoa(player2.life), App.font)};

	if (SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
		SDL_ExitWithError("print_scoreboard : color in white");
	if (SDL_RenderDrawRect(App.renderer, &rect_pos))
		SDL_ExitWithError("print_scoreboard : draw rect");
	rect_pos.y += SCOREBOARD_HEIGHT / 2 - get_text_height("A", App.font) / 2;
	render_text(App.renderer, "Player", player_text_rect, App.font,
		(SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "score", score_text_rect, App.font,
		(SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "life", life_text_rect, App.font, (SDL_Color){255,
		255, 255, 255});
	render_text(App.renderer, ft_itoa(player1.id), id_rect_player1, App.font,
		(SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player1.score), score_rect_player1,
		App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player1.life), life_rect_player1,
		App.font, (SDL_Color){255, 255, 255, 255});
	player_text_rect.x = SCREEN_WIDTH - 20 - get_text_width("Player", App.font)
		- get_text_width("A", App.font);
	score_text_rect.x = SCREEN_WIDTH - 120 - get_text_width("score", App.font)
		- get_text_width("99999", App.font);
	life_text_rect.x = SCREEN_WIDTH - 220 - get_text_width("life", App.font)
		- get_text_width("A", App.font) - get_text_width("99999", App.font);
	render_text(App.renderer, "Player", player_text_rect, App.font,
		(SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "score", score_text_rect, App.font,
		(SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "life", life_text_rect, App.font, (SDL_Color){255,
		255, 255, 255});
	render_text(App.renderer, ft_itoa(player2.id), id_rect_player2, App.font,
		(SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player2.score), score_rect_player2,
		App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player2.life), life_rect_player2,
		App.font, (SDL_Color){255, 255, 255, 255});
}

// ------- Rendu du compte à rebours -------
void	countdown_transition(t_grid grid, t_user_data player1,
		t_user_data player2, t_gametick *gametick, SDL_Rect actions_rect_pos,
		SDL_Rect scoreboard_rect_pos)
{
	const Uint32	countdown_duration = gametick->timer;
	Uint32			start_time;
	Uint32			current_time;
	int				seconds_left;
	char			*countdown_text;
	SDL_Rect		text_rect;
	int				text_w;
	int				text_h;

	// Définir la durée du compte à rebours (en millisecondes)
	start_time = SDL_GetTicks();
	while (App.running && ((current_time = SDL_GetTicks())
			- start_time < countdown_duration))
	{
		// Effacer l'écran en noir
		SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255);
		SDL_RenderClear(App.renderer);

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				App.running = SDL_FALSE;
		}

		print_grid(grid);
		print_snake(grid, player1.head_snake, gametick->snakes_animation);
		print_snake(grid, player2.head_snake, gametick->snakes_animation);
		print_obstacles(grid);
		print_is_pending(grid, gametick->object_cooldown);
		print_actions(actions_rect_pos, player1, player2);
		print_scoreboard(scoreboard_rect_pos, player1, player2);
		// Calcul du nombre de secondes restantes
		seconds_left = (countdown_duration - (current_time - start_time))
			/ 1000;
		if (seconds_left > 0)
			countdown_text = ft_itoa(seconds_left);
		else
			countdown_text = ft_strdup("Go!");
		// Calculer la taille du texte pour le centrer
		text_w = get_text_width(countdown_text, App.font) * 2;
		text_h = get_text_height(countdown_text, App.font) * 2;
		text_rect.x = SCREEN_WIDTH / 2 - text_w / 2;
		text_rect.y = SCREEN_HEIGHT / 2 - text_h / 2;
		text_rect.w = text_w;
		text_rect.h = text_h;
		// Afficher le texte du compte à rebours
		render_text(App.renderer, countdown_text, text_rect, App.font,
			(SDL_Color){255, 255, 255, 255});
		free(countdown_text);
		SDL_RenderPresent(App.renderer);
		SDL_Delay(1000 / 60);
	}
	// mettre à jour le temps écoulé
	gametick->elapsed_time = SDL_GetTicks();
}
