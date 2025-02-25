#include "snake.h"

void	do_input(t_user_data *player1, t_user_data *player2)
{
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
					case SDL_SCANCODE_Q:
						handle_speed(player1);
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
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					handle_speed(player2);
				break;
		}
	}
}