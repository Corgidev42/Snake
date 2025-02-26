# include "snake_together.h"

// Module Game Logic
// Les fonctions qui gèrent les rollbacks et interactions liées aux joueurs (inventaire, bonus, vitesse…).

// --- Fonctions de rollback ou d’animation de mort ----
void	do_rollback_move(t_grid *grid, t_user_data *player)
{
	if (!player || !player->head_snake || !player->head_snake->next)
		return ;
	add_behind_snake_part(player, SDL_FALSE);
	if (get_size_snake(player->head_snake) > 2)
		remove_snake_head_parts(grid, player, 1);
}

void	colls_to_bonk(t_grid *grid, t_user_data *player)
{
	if (player->head_snake->snake_state != BONKED)
	{
		do_rollback_move(grid, player);
		player->speed = 0;
		player->head_snake->snake_state = BONKED;
	}
}
void	died_animation(t_grid *grid, int *died_cooldown, t_user_data *player)
{
	if (*died_cooldown <= 0)
	{
		*died_cooldown += SNAKE_DIED_TIME;
		if (!player->is_star)
			remove_behind_snake_part(grid, player);
	}
}
