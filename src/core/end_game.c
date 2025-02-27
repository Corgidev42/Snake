#include "snake.h"

static SDL_Color	get_color_by_skin(t_color color)
{
	switch (color)
	{
	case YELLOW:
		return (SDL_Color){255, 255, 0, 255};
	case GREEN:
		return (SDL_Color){0, 255, 0, 255};
	case BLUE:
		return (SDL_Color){0, 0, 255, 255};
	default:
		return (SDL_Color){255, 255, 255, 255};
	}
}

void	end_game_window(t_user_data *player1, t_user_data *player2)
{
	// Sur 30% de la hauteur de la fenetre -> "Player {1 ou 2} win !!!"
	// Sur 30% de la hauteur de la fenetre -> "Highest size: {size player 1} {size player 2}"
	// Sur 30% de la hauteur de la fenetre -> "Highest score: {score player 1} {score player 2}"
	// Sur 10% de la hauteur de la fenetre -> "Press any key to exit"
	SDL_Rect	rect_pos = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect	rect_text = {100, 0, 0, 0};
	SDL_Rect	skin_rect = {0, 0, 75, 75};
	SDL_Rect	tmp_rect = {0, 0, 0, 0};
	SDL_Color	color = {255, 255, 255, 255};
	char		*text = NULL;
	char		*tmp = NULL;

	if (SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255))
		SDL_ExitWithError("Color set in black");
	if (SDL_RenderClear(App.renderer))
		SDL_ExitWithError("Render clear");

	// If same life -> draw a draw
	if (player1->life == player2->life && player1->score == player2->score && player1->max_snake_size == player2->max_snake_size)
	{
		rect_pos.y = 0;
		rect_pos.h = SCREEN_HEIGHT / (10 / 3);
		text = "Draw !!!";
		rect_text.w = get_text_width(text, App.font) * 8;
		rect_text.h = get_text_height(text, App.font) * 8;
		rect_text.y = rect_pos.y + rect_pos.h / 2 - rect_text.h / 2;
		render_text(App.renderer, text, rect_text, App.font, color);
		rect_text.x = 100;
	}
	else
	{
		rect_pos.y = 0;
		rect_pos.h = SCREEN_HEIGHT / (10 / 3);
		text = "Player ";
		rect_text.w = get_text_width(text, App.font) * 8;
		rect_text.h = get_text_height(text, App.font) * 8;
		rect_text.y = rect_pos.y + rect_pos.h / 2 - rect_text.h / 2;
		render_text(App.renderer, text, rect_text, App.font, color);

		text = ft_itoa(player1->life ? 1 : 2);
		rect_text.x += rect_text.w;
		rect_text.w = get_text_width(text, App.font) * 8;
		rect_text.h = get_text_height(text, App.font) * 8;
		render_text(App.renderer, text, rect_text, App.font, get_color_by_skin(player1->life ? player1->head_snake->skin : player2->head_snake->skin));
		free(text);

		text = " win !!!";
		rect_text.x += rect_text.w;
		rect_text.w = get_text_width(text, App.font) * 8;
		rect_text.h = get_text_height(text, App.font) * 8;
		render_text(App.renderer, text, rect_text, App.font, color);
		rect_text.x = 100;
	}

	rect_pos.y += rect_pos.h;
	rect_pos.h = SCREEN_HEIGHT / (10 / 2);
	text = "Highest size: ";
	rect_text.w = get_text_width(text, App.font) * 5;
	rect_text.h = get_text_height(text, App.font) * 5;
	rect_text.y = rect_pos.y + rect_pos.h / 2 - rect_text.h / 2;
	render_text(App.renderer, text, rect_text, App.font, color);
	tmp_rect = rect_text;

	// Player 1 Skin
	skin_rect.x = tmp_rect.x + tmp_rect.w;
	skin_rect.y = rect_pos.y + rect_pos.h / 2 - rect_pos.h / 4 - skin_rect.h / 2;
	SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.snake_head[player1->head_snake->skin][NORMAL][LEFT][0], &skin_rect);
	text = ft_itoa(player1->max_snake_size - 1);
	tmp = text;
	text = ft_strjoin(" + ", text);
	free(tmp);
	rect_text.w = get_text_width(text, App.font) * 3;
	rect_text.h = get_text_height(text, App.font) * 3;
	rect_text.x = skin_rect.x + skin_rect.w;
	rect_text.y = skin_rect.y + skin_rect.h / 2 - rect_text.h / 2;
	render_text(App.renderer, text, rect_text, App.font, get_color_by_skin(player1->head_snake->skin));
	free(text);

	// If player 1 size is the highest, display a crown
	if (player1->max_snake_size > player2->max_snake_size)
	{
		tmp_rect.x = rect_text.x + rect_text.w + 30;
		tmp_rect.y = rect_pos.y + rect_pos.h / 2 - rect_pos.h / 4 - rect_text.h / 2;
		tmp_rect.w = 75;
		tmp_rect.h = 75;
		SDL_RenderCopy(App.renderer, App.texture_crown, NULL, &tmp_rect);
	}

	// Player 2 Skin
	skin_rect.x = tmp_rect.x + tmp_rect.w;
	skin_rect.y = rect_pos.y + rect_pos.h / 2 + rect_pos.h / 4 - skin_rect.h / 2;
	SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.snake_head[player2->head_snake->skin][NORMAL][LEFT][0], &skin_rect);
	text = ft_itoa(player2->max_snake_size - 1);
	tmp = text;
	text = ft_strjoin(" + ", text);
	free(tmp);
	rect_text.w = get_text_width(text, App.font) * 3;
	rect_text.h = get_text_height(text, App.font) * 3;
	rect_text.x = skin_rect.x + skin_rect.w;
	rect_text.y = skin_rect.y + skin_rect.h / 2 - rect_text.h / 2;
	render_text(App.renderer, text, rect_text, App.font, get_color_by_skin(player2->head_snake->skin));
	free(text);

	// If player 2 size is the highest, display a crown
	if (player2->max_snake_size > player1->max_snake_size)
	{
		tmp_rect.x = rect_text.x + rect_text.w + 30;
		tmp_rect.y = rect_pos.y + rect_pos.h / 2 + rect_pos.h / 4 - rect_text.h / 2;
		tmp_rect.w = 75;
		tmp_rect.h = 75;
		SDL_RenderCopy(App.renderer, App.texture_crown, NULL, &tmp_rect);
	}
	rect_text.x = 100;

	rect_pos.y += rect_pos.h;
	rect_pos.h = SCREEN_HEIGHT / (10 / 2);
	text = "Highest score: ";
	rect_text.y = rect_pos.y + rect_pos.h / 2 - get_text_height(text, App.font) * 5 / 2;
	rect_text.w = get_text_width(text, App.font) * 5;
	rect_text.h = get_text_height(text, App.font) * 5;
	render_text(App.renderer, text, rect_text, App.font, color);
	tmp_rect = rect_text;

	// Player 1 score
	text = ft_itoa(player1->score);
	rect_text.w = get_text_width(text, App.font) * 3;
	rect_text.h = get_text_height(text, App.font) * 3;
	rect_text.x = tmp_rect.x + tmp_rect.w;
	rect_text.y = rect_pos.y + rect_pos.h / 2 - rect_pos.h / 5 - rect_text.h / 2;
	render_text(App.renderer, text, rect_text, App.font, get_color_by_skin(player1->head_snake->skin));
	free(text);

	// If player 1 score is the highest, display a crown
	if (player1->score > player2->score)
	{
		tmp_rect.x = rect_text.x + rect_text.w + 30;
		tmp_rect.y = rect_pos.y + rect_pos.h / 2 - rect_pos.h / 5 - rect_text.h / 2;
		tmp_rect.w = 75;
		tmp_rect.h = 75;
		SDL_RenderCopy(App.renderer, App.texture_crown, NULL, &tmp_rect);
	}

	// Player 2 score
	text = ft_itoa(player2->score);
	rect_text.w = get_text_width(text, App.font) * 3;
	rect_text.h = get_text_height(text, App.font) * 3;
	rect_text.x = tmp_rect.x + tmp_rect.w;
	rect_text.y = rect_pos.y + rect_pos.h / 2 + rect_pos.h / 5 - rect_text.h / 2;
	render_text(App.renderer, text, rect_text, App.font, get_color_by_skin(player2->head_snake->skin));
	free(text);

	// If Player 2 score is the highest, display a crown
	if (player2->score > player1->score)
	{
		tmp_rect.x = rect_text.x + rect_text.w + 30;
		tmp_rect.y = rect_pos.y + rect_pos.h / 2 + rect_pos.h / 5 - rect_text.h / 2;
		tmp_rect.w = 75;
		tmp_rect.h = 75;
		SDL_RenderCopy(App.renderer, App.texture_crown, NULL, &tmp_rect);
	}
	rect_text.x = 100;

	rect_pos.y += rect_pos.h;
	rect_pos.h = SCREEN_HEIGHT / 10;
	text = "Press any key to exit";
	rect_text.y = rect_pos.y + rect_pos.h / 2 - get_text_height(text, App.font) / 2;
	rect_text.w = get_text_width(text, App.font) * 2;
	rect_text.h = get_text_height(text, App.font) * 2;
	render_text(App.renderer, text, rect_text, App.font, color);

	SDL_RenderPresent(App.renderer);
	SDL_Event	event;
	SDL_Delay(2000);
	SDL_PollEvent(&event);
	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				App.running = SDL_FALSE;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					App.running = SDL_FALSE;
				break;
			}
		}
	}
}
