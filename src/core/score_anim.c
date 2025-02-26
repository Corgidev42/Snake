#include "snake_together.h"

t_score_anim	*create_score_anim(int x, int y, int score, int dy_max, int life_time, SDL_Color color)
{
	t_score_anim	*score_anim;

	score_anim = (t_score_anim *)malloc(sizeof(t_score_anim));
	if (!score_anim)
		return (NULL);
	score_anim->x = x;
	score_anim->y = y;
	score_anim->score = score;
	score_anim->dy_max = dy_max;
	score_anim->life_time = life_time;
	score_anim->time = 1;
	score_anim->color = color;
	return (score_anim);
}

t_score_anim	**create_score_anims(int nb_score_anims)
{
	t_score_anim	**score_anims;
	int				i;

	score_anims = (t_score_anim **)malloc(sizeof(t_score_anim *) * (nb_score_anims + 1));
	if (!score_anims)
		return (NULL);
	i = 0;
	while (i < nb_score_anims)
	{
		score_anims[i] = NULL;
		i++;
	}
	score_anims[nb_score_anims] = NULL;
	return (score_anims);
}

void	destroy_score_anim(t_score_anim *score_anim)
{
	if (score_anim)
		free(score_anim);
}

void	destroy_score_anims(t_score_anim **score_anims)
{
	int	i;

	if (!score_anims)
		return ;
	i = 0;
	while (score_anims[i])
	{
		destroy_score_anim(score_anims[i]);
		i++;
	}
	free(score_anims);
}

void	remove_score_anim(t_score_anim **score_anims, t_score_anim *score_anim)
{
	int	i;

	if (!score_anims || !score_anim)
		return ;
	i = 0;
	while (score_anims[i] != score_anim)
		i++;
	if (!score_anims[i])
		return ;
	destroy_score_anim(score_anims[i]);
	while (score_anims[i + 1])
	{
		score_anims[i] = score_anims[i + 1];
		i++;
	}
	score_anims[i] = NULL;
}

void	add_score_anim(t_score_anim **score_anims, t_score_anim *score_anim)
{
	int	i;

	if (!score_anims || !score_anim)
		return ;
	i = 0;
	while (score_anims[i])
		i++;
	score_anims[i] = score_anim;
	score_anims[i + 1] = NULL;
}

void	update_score_anims(t_score_anim **score_anims, int elapsed_time)
{
	int	i;

	if (!score_anims)
		return ;
	i = 0;
	while (score_anims[i])
	{
		score_anims[i]->time += elapsed_time;
		if (score_anims[i]->time >= score_anims[i]->life_time)
			remove_score_anim(score_anims, score_anims[i]);
		else
		{
			score_anims[i]->y -= score_anims[i]->dy_max * elapsed_time / score_anims[i]->life_time;
			score_anims[i]->color.a = 255 - 255 * score_anims[i]->time / score_anims[i]->life_time;
			i++;
		}
	}
}

void	add_snake_size_score_anim(t_score_anim **score_anims, t_user_data *player)
{
	SDL_Color	color;
	int			x;
	int			y;

	color = (SDL_Color){255, 255, 255, 255};
	if (player->id == 1)
	{
		x = SCOREBOARD_POS_X + 120 + get_text_width("score", App.font) + 5 + get_text_width(ft_itoa(player->score), App.font) + 5 + get_text_width("A", App.font) / 2 + 20;
		y = SCOREBOARD_POS_Y + get_text_height("score", App.font) / 2;
	}
	else
	{
		x = SCREEN_WIDTH - 120 + get_text_width(ft_itoa(player->score), App.font) - get_text_width("99999", App.font) + 5 - get_text_width("A", App.font) / 2 + 20;
		y = SCOREBOARD_POS_Y + get_text_height("score", App.font) / 2;
	}
	add_score_anim(score_anims, create_score_anim(x, y, get_size_snake(player->head_snake), SCORE_ANIM_DY, SCORE_ANIM_LIFE_TIME, color));
}

void	do_score_snake_size(int *score_snake_size_cooldown, t_user_data *player1, t_user_data *player2, t_score_anim **score_anims)
{
	if (*score_snake_size_cooldown <= 0)
	{
		add_snake_size_score_anim(score_anims, player1);
		player1->score += get_size_snake(player1->head_snake);

		add_snake_size_score_anim(score_anims, player2);
		player2->score += get_size_snake(player2->head_snake);
		
		*score_snake_size_cooldown += SCORE_SNAKE_SIZE_TIME;
	}
}

void	add_snake_score_anim(t_score_anim **score_anims, t_snake_part *head_snake, int score, t_color color_type)
{
	SDL_Color		color;
	int				x;
	int				y;

	switch (color_type)
	{
	case YELLOW:
		color = (SDL_Color){255, 255, 0, 255};
		break;
	case GREEN:
		color = (SDL_Color){0, 255, 0, 255};
		break;
	case BLUE:
		color = (SDL_Color){0, 0, 255, 255};
		break;
	default:
		color = (SDL_Color){255, 255, 255, 255};
		break;
	}

	x = GRID_POS_X + head_snake->coords.x * CELL_WIDTH + CELL_WIDTH / 2;
	y = GRID_POS_Y + head_snake->coords.y * CELL_HEIGHT + CELL_HEIGHT / 2;

	// Decalage pour afficher le score devant la tete du serpent
	switch (head_snake->orientation)
	{
	case UP:
		y -= CELL_HEIGHT;
		break;
	case DOWN:
		y += CELL_HEIGHT;
		break;
	case LEFT:
		x -= CELL_WIDTH;
		break;
	case RIGHT:
		x += CELL_WIDTH;
		break;	
	default:
		break;
	}

	add_score_anim(score_anims, create_score_anim(x, y, score, SCORE_ANIM_DY, SCORE_ANIM_LIFE_TIME, color));
}

void	print_score_anims(t_score_anim **score_anims, SDL_Renderer *renderer, TTF_Font *font)
{
	int			i;
	char		*score_str;
	SDL_Surface	*text_surface;
	SDL_Texture	*text_texture;
	SDL_Rect	text_rect;

	if (!score_anims)
		return ;
	i = 0;
	while (score_anims[i])
	{
		if (score_anims[i]->score < 0)
			score_str = "-";
		else
			score_str = "+";
		score_str = ft_strjoin(score_str, ft_itoa(score_anims[i]->score));
		text_rect.w = get_text_width(score_str, font);
		text_rect.h = get_text_height(score_str, font);
		text_rect.x = score_anims[i]->x - text_rect.w / 2;
		text_rect.y = score_anims[i]->y;
		
		render_text(renderer, score_str, text_rect, font, score_anims[i]->color);
		free(score_str);
		i++;
	}
}