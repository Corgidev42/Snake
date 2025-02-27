#include "snake_together.h"

// Module Game Logic
// Les fonctions qui gèrent les actions et interactions liées aux joueurs (inventaire, bonus, vitesse…).

// ------- Gestion des bonus et des actions -------
void	add_inventory_bonus(t_user_data *player, t_bonus bonus)
{
	if (bonus == TP)
	{
		if (player->inventory[1] == BONUS_EMPTY)
			player->inventory[1] = TP;
		else if (player->inventory[0] == BONUS_EMPTY)
			player->inventory[0] = TP;
		return ;
	}
	if (player->inventory[0] == BONUS_EMPTY)
		player->inventory[0] = bonus;
	else if (player->inventory[1] == BONUS_EMPTY)
		player->inventory[1] = bonus;
}

void	handle_speed(t_user_data *player)
{
	if (!player->is_speed && player->nb_apple_speed > 0)
	{
		player->is_speed = SDL_TRUE;
		player->speed = SCALE_SPEED;
	}
}

void	remove_bonus_slot(t_user_data *player, int slot)
{
	player->inventory[slot] = BONUS_EMPTY;
	if (player->inventory[1] != BONUS_EMPTY && player->inventory[1] != TP
		&& player->inventory[0] == BONUS_EMPTY)
	{
		player->inventory[0] = player->inventory[1];
		player->inventory[1] = BONUS_EMPTY;
	}
}

void	handle_bonus(t_user_data *player)
{
	switch (player->inventory[0])
	{
	case LIFE_UP:
		player->life += 1;
		break ;
	case STAR:
		player->is_star = SDL_TRUE;
		break ;
	case SLOW:
		player->is_slow = SDL_TRUE;
		break ;
	default:
		return ;
	}
	remove_bonus_slot(player, 0);
}

void	do_actions(t_user_data *player1, t_user_data *player2,
		t_gametick *gametick)
{
	if (player1->is_speed && gametick->snake_1_speed_cooldown <= 0)
	{
		gametick->snake_1_speed_cooldown += SNAKE_SPEED_TIME;
		player1->nb_apple_speed -= 1;
		if (player1->nb_apple_speed == 0)
		{
			player1->is_speed = SDL_FALSE;
			if (!(player1->head_snake->snake_state == BONKED))
				player1->speed = BASE_SPEED;
		}
	}
	if (player1->is_star && gametick->snake_1_star_cooldown <= 0)
	{
		player1->is_star = SDL_FALSE;
		gametick->snake_1_star_cooldown = STAR_COOLDOWN;
		player1->head_snake->snake_state = NORMAL;
		player1->speed = BASE_SPEED;
	}
	if (player1->is_slow && gametick->snake_1_slow_cooldown <= 0)
	{
		player1->is_slow = SDL_FALSE;
		gametick->snake_1_slow_cooldown = SLOW_COOLDOWN;
	}
	if (player2->is_speed && gametick->snake_2_speed_cooldown <= 0)
	{
		gametick->snake_2_speed_cooldown += SNAKE_SPEED_TIME;
		player2->nb_apple_speed -= 1;
		if (player2->nb_apple_speed == 0)
		{
			player2->is_speed = SDL_FALSE;
			if (!(player2->head_snake->snake_state == BONKED))
				player2->speed = BASE_SPEED;
		}
	}
	if (player2->is_star && gametick->snake_2_star_cooldown <= 0)
	{
		player2->is_star = SDL_FALSE;
		gametick->snake_2_star_cooldown = STAR_COOLDOWN;
		player2->head_snake->snake_state = NORMAL;
		player2->speed = BASE_SPEED;
	}
	if (player2->is_slow && gametick->snake_2_slow_cooldown <= 0)
	{
		player2->is_slow = SDL_FALSE;
		gametick->snake_2_slow_cooldown = SLOW_COOLDOWN;
	}
}
