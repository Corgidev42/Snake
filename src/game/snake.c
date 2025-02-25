#include "snake.h"

t_snake_part	*add_behind_snake_part(t_snake_part *head_snake)
{
	t_snake_part	*new_snake_part;
	t_snake_part	*current;

	new_snake_part = malloc(sizeof(t_snake_part));
	if (!new_snake_part)
		SDL_ExitWithError("malloc new_snake_part");
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

void	move_snake(t_grid *grid, int *snake_cooldown, t_user_data *player)
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
			// grid->cells
			prev = current;
			current = prev->next;
			if (current->next == NULL)
			{
				if (current->coords.x > 0 && current->coords.x < GRID_COLS
					&& current->coords.y > 0 && current->coords.y < GRID_ROWS)
					grid->cells[current->coords.x][current->coords.y].has_snake = SDL_FALSE;
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
		if (player->head_snake->coords.x > 0 && player->head_snake->coords.x < GRID_COLS
			&& player->head_snake->coords.y > 0 && player->head_snake->coords.y < GRID_ROWS)
			grid->cells[player->head_snake->coords.x][player->head_snake->coords.y].has_snake = SDL_TRUE;
		*snake_cooldown += SNAKE_MOVE_TIME;
	}
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
		if (current->coords.x < 0 || current->coords.x >= GRID_COLS
			|| current->coords.y < 0 || current->coords.y >= GRID_ROWS)
			break;
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