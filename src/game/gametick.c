#include "snake.h"

void	init_gametick(t_gametick *gametick)
{
	gametick->elapsed_time = SDL_GetTicks();
	gametick->apple_cooldown = APPLE_GENERATION_TIME;
	gametick->object_cooldown = OBJECT_GENERATION_TIME / 2;
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