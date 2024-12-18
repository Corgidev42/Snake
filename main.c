#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define ROWS 10
# define COLS 10
# define CELL_HEIGHT (SCREEN_HEIGHT / ROWS)
# define CELL_WIDTH (SCREEN_WIDTH / COLS)
# define PADDING 35
# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4

typedef struct		s_app
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_bool		running;
}					t_app;

typedef struct		s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef struct		s_snake
{
	t_coords		coords;
	int				orientation;
	struct s_snake	*next;
}					t_snake;

t_app				app;
t_snake				*head_snake;
t_coords			apple;

void	SDL_ExitWithError(const char *message)
{
	SDL_Log("ERRORR : %s > %s\n", message, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void	do_orientation(SDL_Keycode keycode)
{
	switch (keycode)
	{
		case SDLK_UP:
			if (head_snake->orientation != DOWN)
				head_snake->orientation = UP;
			break;
		case SDLK_DOWN:
			if (head_snake->orientation != UP)
				head_snake->orientation = DOWN;
			break;
		case SDLK_LEFT:
			if (head_snake->orientation != RIGHT)
				head_snake->orientation = LEFT;
			break;
		case SDLK_RIGHT:
			if (head_snake->orientation != LEFT)
				head_snake->orientation = RIGHT;
			break;
		default:
			break;
	}
}

void	do_input()
{
	SDL_Event	event;
	int			nb_events;

	nb_events = 0;
	while (!nb_events && SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				nb_events = 1;
				do_orientation(event.key.keysym.sym);
				break;
			case SDL_QUIT:
				app.running = SDL_FALSE;
				break;
			default:
				break;
		}
	}
}

void	move_snake()
{
	t_snake	*prev_snake;
	t_snake	*current_snake;

	prev_snake = head_snake;
	current_snake = head_snake;
	while (current_snake)
	{
		prev_snake = current_snake;
		current_snake = prev_snake->next;
		if (current_snake && current_snake->next == NULL)
		{
			current_snake->next = head_snake;
			prev_snake->next = NULL;

			current_snake->coords.x = head_snake->coords.x;
			current_snake->coords.y = head_snake->coords.y;
			current_snake->orientation = head_snake->orientation;

			head_snake = current_snake;
			break;
		}
	}
	switch (head_snake->orientation)
	{
		case UP:
			head_snake->coords.y += -1;
			if (head_snake->coords.y == -1)
				head_snake->coords.y += ROWS;
			break;
		case DOWN:
			head_snake->coords.y += 1;
			if (head_snake->coords.y == ROWS)
				head_snake->coords.y += -ROWS;
			break;
		case LEFT:
			head_snake->coords.x += -1;
			if (head_snake->coords.x == -1)
				head_snake->coords.x += COLS;
			break;
		case RIGHT:
			head_snake->coords.x += 1;
			if (head_snake->coords.x == COLS)
				head_snake->coords.x += -COLS;
			break;
		default:
			break;
	}
}

void	generate_apple()
{
	t_snake *temp;
	apple.x = rand() % COLS;
	apple.y = rand() % ROWS;

	temp = head_snake;
	while (temp)
	{
		if (temp->coords.x == apple.x && temp->coords.y == apple.y)
		{
			generate_apple();
			break;
		}
		temp = temp->next;
	}
}

void	just_dont_eat()
{
	t_snake	*temp;

	temp = head_snake->next;
	while (temp)
	{
		if (temp->coords.x == head_snake->coords.x && temp->coords.y == head_snake->coords.y)
		{
			printf("YOU LOOSE BIG L !");
			app.running = SDL_FALSE;
			break;
		}
		temp = temp->next;
	}
}


void	just_do_eat()
{
	int	size_snake;

	size_snake = 0;
	if (head_snake->coords.x == apple.x && head_snake->coords.y == apple.y)
	{
		t_snake	*new_part;
		t_snake	*temp;

		temp = head_snake;
		while(temp)
		{
			if (temp->next == NULL)
			{
				new_part = malloc(sizeof(t_snake));
				temp->next = new_part;
				new_part->orientation = temp->orientation;
				new_part->next = NULL;
				new_part->coords.x = temp->coords.x;
				new_part->coords.y = temp->coords.y;
				switch (new_part->orientation)
				{
				case UP:
 					new_part->coords.y += 1;
					break;
				case DOWN:
 					new_part->coords.y += -1;
					break;
				case LEFT:
 					new_part->coords.x += 1;
					break;
				case RIGHT:
 					new_part->coords.x += -1;
					break;
				default:
					break;
				}
				break;
			}
			temp = temp->next;
			size_snake++;
		}
		if (size_snake == COLS * ROWS - 1)
		{
			printf("YOU WIN !!");
			app.running = SDL_FALSE;
		}
		else
			generate_apple();
	}
}

void	print_grid()
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE))
		SDL_ExitWithError("Error Set Color to White");
	while (i < COLS)
	{
		j += CELL_WIDTH;
		if(SDL_RenderDrawLine(app.renderer, j, 0, j, SCREEN_HEIGHT))
			SDL_ExitWithError("Error Draw Cols Lines");
		i++;
	}
	i = 0;
	j = 0;
	while (i < ROWS)
	{
		j += CELL_HEIGHT;
		if (SDL_RenderDrawLine(app.renderer, 0, j, SCREEN_WIDTH, j))
			SDL_ExitWithError("Error Draw Rows Lines");
		i++;
	}
}
void	print_snake()
{
	SDL_Rect	snake_rect;
	int			i;
	t_snake		*current_snake;

	snake_rect.h = CELL_HEIGHT;
	snake_rect.w = CELL_WIDTH;

	i = 0;
	current_snake = head_snake;
	while (current_snake)
	{
		snake_rect.y = current_snake->coords.y * CELL_HEIGHT;
		snake_rect.x = current_snake->coords.x * CELL_WIDTH;

		if (i == 0 && SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, SDL_ALPHA_OPAQUE)) // HEAD_SNAKE
				SDL_ExitWithError("Error Set Color to Green for Head Snake");
		else if (i != 0 && SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, SDL_ALPHA_OPAQUE)) //BODY_SNAKE
				SDL_ExitWithError("Error Set Color to Blue for Head Snake");

		if (SDL_RenderFillRect(app.renderer, &snake_rect))
			SDL_ExitWithError("Error Fill Rect Head of Snake");
		i++;
		current_snake = current_snake->next;
	}

}
void	print_apple()
{
	SDL_Rect apple_rect;

	apple_rect.h = CELL_HEIGHT - (PADDING * 2);
	apple_rect.w = CELL_WIDTH - (PADDING * 2);
	apple_rect.y = apple.y * CELL_HEIGHT + PADDING;
	apple_rect.x = apple.x * CELL_WIDTH + PADDING;

	if (SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, SDL_ALPHA_OPAQUE))
		SDL_ExitWithError("Error Set Color to RED");
	if (SDL_RenderFillRect(app.renderer, &apple_rect))
		SDL_ExitWithError("Error Draw Apple");
}

int		main(int argc, char *argv[])
{
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO))
		SDL_ExitWithError("Init Error");

	app.window = SDL_CreateWindow("Snake by X", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP);
	if (!app.window)
		SDL_ExitWithError("Window Create Error");

	app.renderer = SDL_CreateRenderer(app.window, -1 , SDL_RENDERER_SOFTWARE);
	if (!app.renderer)
		SDL_ExitWithError("Renderer Create Error");

	app.running = SDL_TRUE;

	head_snake = malloc(sizeof(t_snake));
	head_snake->coords.x = COLS / 2;
	head_snake->coords.y = ROWS / 2;

	generate_apple();

	while (app.running)
	{
		if (SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE))
			SDL_ExitWithError("Error Set Color to Black");

		if (SDL_RenderClear(app.renderer))
			SDL_ExitWithError("Error Render Clear");

		do_input();
		move_snake();
		just_dont_eat();
		just_do_eat();

		print_grid();
		print_snake();
		print_apple();

		SDL_RenderPresent(app.renderer);

		SDL_Delay(250);
	}

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	SDL_Quit();
	return (0);
}
