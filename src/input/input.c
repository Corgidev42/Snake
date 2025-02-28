#include "snake_together.h"

// Ce module se charge de récupérer et traiter les entrées utilisateur, que ce soit pendant le jeu ou dans le menu.

// ------- Gestion des événements en jeu  -------

void	do_input(t_user_data *player1, t_user_data *player2)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			App.running = SDL_FALSE;
			break ;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				App.running = SDL_FALSE;
				break ;
			case SDL_SCANCODE_A:
				rotate_snake(player1, LEFT);
				break ;
			case SDL_SCANCODE_D:
				rotate_snake(player1, RIGHT);
				break ;
			case SDL_SCANCODE_W:
				rotate_snake(player1, UP);
				break ;
			case SDL_SCANCODE_S:
				rotate_snake(player1, DOWN);
				break ;
			case SDL_SCANCODE_Q:
				if (!(player1->head_snake->snake_state == BONKED))
					handle_speed(player1);
				break ;
			case SDL_SCANCODE_E:
				handle_bonus(player1);
				break ;
			case SDL_SCANCODE_LEFT:
				rotate_snake(player2, LEFT);
				break ;
			case SDL_SCANCODE_RIGHT:
				rotate_snake(player2, RIGHT);
				break ;
			case SDL_SCANCODE_UP:
				rotate_snake(player2, UP);
				break ;
			case SDL_SCANCODE_DOWN:
				rotate_snake(player2, DOWN);
				break ;
			default:
				break ;
			}
			break ;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT && !(player2->head_snake->snake_state == BONKED))
				handle_speed(player2);
			if (event.button.button == SDL_BUTTON_RIGHT)
				handle_bonus(player2);
			break ;
		}
	}
}

// ------- Gestion des entrées dans le menu  -------

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
				break ;
			case SDL_SCANCODE_SPACE:
				player1->is_ready = (player1->is_ready ? SDL_FALSE : SDL_TRUE);
				if (player1->is_ready
					&& player1->head_snake->skin == player2->head_snake->skin)
					player2->head_snake->skin = (player2->head_snake->skin == 0 ? NB_COLORS
							- 1 : player2->head_snake->skin - 1);
				break ;
			case SDL_SCANCODE_RETURN:
				player2->is_ready = (player2->is_ready ? SDL_FALSE : SDL_TRUE);
				if (player2->is_ready
					&& player1->head_snake->skin == player2->head_snake->skin)
					player1->head_snake->skin = (player1->head_snake->skin == 0 ? NB_COLORS
							- 1 : player1->head_snake->skin - 1);
				break ;
			case SDL_SCANCODE_A:
				player1->head_snake->skin = (player1->head_snake->skin == 0 ? NB_COLORS
						- 1 : player1->head_snake->skin - 1);
				if (player2->is_ready
					&& player1->head_snake->skin == player2->head_snake->skin)
					player1->head_snake->skin = (player1->head_snake->skin == 0 ? NB_COLORS
							- 1 : player1->head_snake->skin - 1);
				player1->is_ready = SDL_FALSE;
				break ;
			case SDL_SCANCODE_D:
				player1->head_snake->skin = (player1->head_snake->skin == NB_COLORS
						- 1 ? 0 : player1->head_snake->skin + 1);
				if (player2->is_ready
					&& player1->head_snake->skin == player2->head_snake->skin)
					player1->head_snake->skin = (player1->head_snake->skin == NB_COLORS
							- 1 ? 0 : player1->head_snake->skin + 1);
				player1->is_ready = SDL_FALSE;
				break ;
			case SDL_SCANCODE_LEFT:
				player2->head_snake->skin = (player2->head_snake->skin == 0 ? NB_COLORS
						- 1 : player2->head_snake->skin - 1);
				if (player1->is_ready
					&& player1->head_snake->skin == player2->head_snake->skin)
					player2->head_snake->skin = (player2->head_snake->skin == 0 ? NB_COLORS
							- 1 : player2->head_snake->skin - 1);
				player2->is_ready = SDL_FALSE;
				break ;
			case SDL_SCANCODE_RIGHT:
				player2->head_snake->skin = (player2->head_snake->skin == NB_COLORS
						- 1 ? 0 : player2->head_snake->skin + 1);
				if (player1->is_ready
					&& player1->head_snake->skin == player2->head_snake->skin)
					player2->head_snake->skin = (player2->head_snake->skin == NB_COLORS
							- 1 ? 0 : player2->head_snake->skin + 1);
				player2->is_ready = SDL_FALSE;
				break ;
			case SDL_SCANCODE_1:
				handle_bonus_active(LIFE_UP);
				break ;
			case SDL_SCANCODE_2:
				handle_bonus_active(TP);
				break ;
			case SDL_SCANCODE_3:
				handle_bonus_active(STAR);
				break ;
			case SDL_SCANCODE_4:
				handle_bonus_active(SLOW);
				break ;
			default:
				break ;
			}
			break ;
		case SDL_QUIT:
			App.running = SDL_FALSE;
			break ;
		default:
			break ;
		}
	}
}
