#include "snake.h"

void	init_gametick(t_gametick *gametick)
{
	gametick->elapsed_time = SDL_GetTicks();
	gametick->apple_cooldown = APPLE_GENERATION_TIME;
	gametick->object_cooldown = OBJECT_GENERATION_TIME / 2;

	gametick->snake_1_cooldown = SNAKE_MOVE_TIME;
	gametick->snake_1_speed_cooldown = SNAKE_SPEED_TIME;
	gametick->snake_1_star_cooldown = STAR_COOLDOWN;
	gametick->snake_1_slow_cooldown = SLOW_COOLDOWN;
	gametick->snake_1_died_cooldown = SNAKE_DIED_TIME;
	
	gametick->snake_2_cooldown = SNAKE_MOVE_TIME;
	gametick->snake_2_speed_cooldown = SNAKE_SPEED_TIME;
	gametick->snake_2_star_cooldown = STAR_COOLDOWN;
	gametick->snake_2_slow_cooldown = SLOW_COOLDOWN;
	gametick->snake_2_died_cooldown = SNAKE_DIED_TIME;

	gametick->snakes_animation = SNAKES_ANIMATION_TIME;

	gametick->timer = TIMER_BEFORE_START;
}

void	update_gametick(t_gametick *gametick, t_user_data *player1, t_user_data *player2)
{
	int	elapsed_time = SDL_GetTicks() - gametick->elapsed_time;

	gametick->apple_cooldown -= elapsed_time;
	gametick->object_cooldown -= elapsed_time;
	gametick->snake_1_cooldown -= (int)(elapsed_time * player1->speed * (player2->is_slow ? SCALE_SLOW : 1));
	gametick->snake_2_cooldown -= (int)(elapsed_time * player2->speed * (player1->is_slow ? SCALE_SLOW : 1));
	if (player1->head_snake->snake_state == BONKED)
		gametick->snake_1_died_cooldown -= elapsed_time;
	if (player2->head_snake->snake_state == BONKED)
		gametick->snake_2_died_cooldown -= elapsed_time;
	gametick->snakes_animation -= elapsed_time;

	if (player1->is_speed)
		gametick->snake_1_speed_cooldown -= elapsed_time;
	if (player1->is_star)
		gametick->snake_1_star_cooldown -= elapsed_time;
	if (player1->is_slow)
		gametick->snake_1_slow_cooldown -= elapsed_time;

	if (player2->is_speed)
		gametick->snake_2_speed_cooldown -= elapsed_time;
	if (player2->is_star)
		gametick->snake_2_star_cooldown -= elapsed_time;
	if (player2->is_slow)
		gametick->snake_2_slow_cooldown -= elapsed_time;

	if (gametick->snakes_animation <= 0)
		gametick->snakes_animation += SNAKES_ANIMATION_TIME;
	gametick->elapsed_time = SDL_GetTicks();
}
