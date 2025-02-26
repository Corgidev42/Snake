#include "snake.h"

int	find_bonus_index(t_bonus bonus)
{
	int	current_bonus_index = 0;

	while (current_bonus_index < App.nb_bonus)
	{
		if (App.available_bonus[current_bonus_index] == bonus)
			return (current_bonus_index);
		current_bonus_index++;
	}
	return (-1);
}

void	handle_bonus_active(t_bonus bonus)
{
	int	current_bonus_index = 0;
	int	find_index = find_bonus_index(bonus);

	if (find_index == -1)
	{
		App.available_bonus[App.nb_bonus] = bonus;
		App.nb_bonus++;
	}
	else
	{
		current_bonus_index = find_index;
		while (current_bonus_index < App.nb_bonus - 1)
		{
			App.available_bonus[current_bonus_index] = App.available_bonus[current_bonus_index + 1];
			current_bonus_index++;
		}
		App.nb_bonus--;
	}
}

void	menu_do_input(t_user_data *player1, t_user_data *player2)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					App.running = SDL_FALSE;
					break;
				case SDL_SCANCODE_SPACE:
					player1->is_ready = (player1->is_ready ? SDL_FALSE : SDL_TRUE);
					if (player1->is_ready && player1->head_snake->skin == player2->head_snake->skin)
						player2->head_snake->skin = (player2->head_snake->skin == 0 ? NB_COLORS - 1 : player2->head_snake->skin - 1);
					break;
				case SDL_SCANCODE_RETURN:
					player2->is_ready = (player2->is_ready ? SDL_FALSE : SDL_TRUE);
					if (player2->is_ready && player1->head_snake->skin == player2->head_snake->skin)
						player1->head_snake->skin = (player1->head_snake->skin == 0 ? NB_COLORS - 1 : player1->head_snake->skin - 1);
					break;
				case SDL_SCANCODE_A:
					player1->head_snake->skin = (player1->head_snake->skin == 0 ? NB_COLORS - 1 : player1->head_snake->skin - 1);
					if (player2->is_ready && player1->head_snake->skin == player2->head_snake->skin)
						player1->head_snake->skin = (player1->head_snake->skin == 0 ? NB_COLORS - 1 : player1->head_snake->skin - 1);
					player1->is_ready = SDL_FALSE;
					break;
				case SDL_SCANCODE_D:
					player1->head_snake->skin = (player1->head_snake->skin == NB_COLORS - 1 ? 0 : player1->head_snake->skin + 1);
					if (player2->is_ready && player1->head_snake->skin == player2->head_snake->skin)
						player1->head_snake->skin = (player1->head_snake->skin == NB_COLORS - 1 ? 0 : player1->head_snake->skin + 1);
					player1->is_ready = SDL_FALSE;
					break;
				case SDL_SCANCODE_LEFT:
					player2->head_snake->skin = (player2->head_snake->skin == 0 ? NB_COLORS - 1 : player2->head_snake->skin - 1);
					if (player1->is_ready && player1->head_snake->skin == player2->head_snake->skin)
						player2->head_snake->skin = (player2->head_snake->skin == 0 ? NB_COLORS - 1 : player2->head_snake->skin - 1);
					player2->is_ready = SDL_FALSE;
					break;
				case SDL_SCANCODE_RIGHT:
					player2->head_snake->skin = (player2->head_snake->skin == NB_COLORS - 1 ? 0 : player2->head_snake->skin + 1);
					if (player1->is_ready && player1->head_snake->skin == player2->head_snake->skin)
						player2->head_snake->skin = (player2->head_snake->skin == NB_COLORS - 1 ? 0 : player2->head_snake->skin + 1);
					player2->is_ready = SDL_FALSE;
					break;
				case SDL_SCANCODE_1:
					handle_bonus_active(LIFE_UP);
					break;
				case SDL_SCANCODE_2:
					handle_bonus_active(TP);
					break;
				case SDL_SCANCODE_3:
					handle_bonus_active(STAR);
					break;
				case SDL_SCANCODE_4:
					handle_bonus_active(SLOW);
					break;
				default:
					break;
				}
				break;
			case SDL_QUIT:
				App.running = SDL_FALSE;
				break;
			default:
				break;
		}
	}
}

void	print_player_choice(SDL_Rect rect_side, t_user_data player)
{
	char	*text_id = "Player ";

	// print player id
	text_id = ft_strjoin(text_id, ft_itoa(player.id));
	SDL_Rect	rect_text = {rect_side.x + rect_side.w / 2 - get_text_width(text_id, App.font), rect_side.y, get_text_width(text_id, App.font) * 2, get_text_height(text_id, App.font) * 2};
	render_text(App.renderer, text_id, rect_text, App.font, (SDL_Color){255, 255, 255, 255});
	free(text_id);

	// print snake color
	SDL_Rect	rect_snake = {rect_side.x + rect_side.w / 2 - 50, rect_side.y + 50, 100, 100};
	SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.snake_head[player.head_snake->skin][NORMAL][DOWN][4], &rect_snake);

	// print ready status + left right button
	if (player.is_ready)
	{
		SDL_Rect	rect_ready = {rect_side.x + rect_side.w / 2 - 50, rect_side.y + 200, get_text_width("READY !", App.font) * 2, get_text_height("READY !", App.font) * 2};
		render_text(App.renderer, "READY !", rect_ready, App.font, (SDL_Color){255, 255, 255, 255});
	}
	else
	{
		char	*text_ready = "Press ";
		char	*left_btn = (player.id == 1 ? "a" : "<");
		char	*right_btn = (player.id == 1 ? "d" : ">");
		text_ready = ft_strjoin(text_ready, (player.id == 1 ? "space" : "enter"));
		SDL_Rect	rect_ready = {rect_side.x + rect_side.w / 2 - get_text_width(text_ready, App.font), rect_side.y + 200, get_text_width(text_ready, App.font) * 2, get_text_height(text_ready, App.font) * 2};
		render_text(App.renderer, text_ready, rect_ready, App.font, (SDL_Color){255, 255, 255, 255});
		// Left and right button
		SDL_Rect	rect_left = {rect_ready.x - get_text_width(left_btn, App.font) * 2 - 25, rect_ready.y, get_text_width(left_btn, App.font) * 2, get_text_height(left_btn, App.font) * 2};
		SDL_Rect	rect_right = {rect_ready.x + get_text_width(text_ready, App.font) * 2 + 25, rect_ready.y, get_text_width(right_btn, App.font) * 2, get_text_height(right_btn, App.font) * 2};
		render_text(App.renderer, left_btn, rect_left, App.font, (SDL_Color){255, 255, 255, 255});
		render_text(App.renderer, right_btn, rect_right, App.font, (SDL_Color){255, 255, 255, 255});
		
		free(text_ready);
	}
}

void	print_bonus_choice(SDL_Rect rect)
{
	// print bonus choice
	char	*text_bonus = "Choose your bonus (1, 2, 3, 4)";
	SDL_Rect	rect_bonus = {rect.x + rect.w / 2 - get_text_width(text_bonus, App.font), rect.y + 50, get_text_width(text_bonus, App.font) * 2, get_text_height(text_bonus, App.font) * 2};
	render_text(App.renderer, text_bonus, rect_bonus, App.font, (SDL_Color){255, 255, 255, 255});

	// print bonus
	SDL_Rect	rect_bonus_life = {rect.x + rect.w / 2 - 300, rect.y + 100, 100, 100};
	SDL_Rect	rect_bonus_tp = {rect.x + rect.w / 2 - 150, rect.y + 100, 100, 100};
	SDL_Rect	rect_bonus_star = {rect.x + rect.w / 2, rect.y + 100, 100, 100};
	SDL_Rect	rect_bonus_slow = {rect.x + rect.w / 2 + 150, rect.y + 100, 100, 100};

	SDL_RenderCopy(App.renderer, App.texture_bonus.life_up, NULL, &rect_bonus_life);
	if (find_bonus_index(LIFE_UP) == -1)
		SDL_RenderCopy(App.renderer, App.texture_cross, NULL, &rect_bonus_life);
	SDL_RenderCopy(App.renderer, App.texture_bonus.tp, NULL, &rect_bonus_tp);
	if (find_bonus_index(TP) == -1)
		SDL_RenderCopy(App.renderer, App.texture_cross, NULL, &rect_bonus_tp);
	SDL_RenderCopy(App.renderer, App.texture_bonus.star, NULL, &rect_bonus_star);
	if (find_bonus_index(STAR) == -1)
		SDL_RenderCopy(App.renderer, App.texture_cross, NULL, &rect_bonus_star);
	SDL_RenderCopy(App.renderer, App.texture_bonus.slow, NULL, &rect_bonus_slow);
	if (find_bonus_index(SLOW) == -1)
		SDL_RenderCopy(App.renderer, App.texture_cross, NULL, &rect_bonus_slow);
}

void	menu_window(t_user_data *player1, t_user_data *player2)
{
	SDL_Rect	rect_left;
	SDL_Rect	rect_right;
	SDL_Rect	rect_bonus;

	rect_left.x = 0, rect_left.y = 0, rect_left.h = SCREEN_HEIGHT / 2, rect_left.w = SCREEN_WIDTH / 2;
	rect_right.x = SCREEN_WIDTH / 2, rect_right.y = 0, rect_right.h = SCREEN_HEIGHT / 2, rect_right.w = SCREEN_WIDTH / 2;
	rect_bonus.x = 0, rect_bonus.y = SCREEN_HEIGHT / 2, rect_bonus.h = SCREEN_HEIGHT / 2, rect_bonus.w = SCREEN_WIDTH;
	
	while (App.running && (!player1->is_ready || !player2->is_ready))
	{
		SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255);
		SDL_RenderClear(App.renderer);

		menu_do_input(player1, player2);

		print_player_choice(rect_left, *player1);
		print_player_choice(rect_right, *player2);

		print_bonus_choice(rect_bonus);

		SDL_RenderPresent(App.renderer);
	}
}
