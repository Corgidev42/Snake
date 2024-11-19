#include <SDL2/SDL.h>

typedef struct s_app
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_bool		running;
}					t_app;

typedef struct s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef struct s_snake
{
	t_coords		coords;
	t_snake			*next;
}					t_snake;

t_app				app;
t_snake				snake;
t_coords			apple;

int	main(int argc, char *argv[])
{
	/*
		Initailisation de SDL
		Initiliasation de la fenetre
		et ensuite du rendu
		*/
	app.running = SDL_TRUE;
	while (app.running)
	{
		clear_renderer();

		do_intput();
		move_snake();

		print_grid();
		print_snake();
		print_apple();

		present_renderer();

		SDL_Delay(800);
	}

	/*
		Free de tous le bordel + quitter le programme
	*/
	return (0);
}
