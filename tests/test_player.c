#include <stdio.h>

#include "tests.h"
#include "player.h"

void test_init_players(void)
{
	int	assert_file = 1;
	// Déclare les structures à initialiser
	t_user_data player1;
	t_user_data player2;

	// Appelle la fonction d'initialisation
	init_players(&player1, &player2);

	// Vérifie les valeurs du joueur 1
	assert(player1.id == 1);
	assert(player1.is_ready == SDL_FALSE);
	assert(player1.score == 0);
	assert(player1.life == LIFE_MAX);

	// Vérifie l'inventaire du joueur 1
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		assert(player1.inventory[i] == BONUS_EMPTY);
	}

	// Vérifie la tête du snake du joueur 1
	assert(player1.head_snake != NULL);
	assert(player1.head_snake->coords.x == -1);
	assert(player1.head_snake->coords.y == -1);
	assert(player1.head_snake->orientation == UP);
	assert(player1.head_snake->speed == BASE_SPEED);
	assert(player1.head_snake->skin == YELLOW);
	assert(player1.head_snake->next == NULL);

	// Répète les mêmes vérifications pour le joueur 2
	assert(player2.id == 2);
	assert(player2.is_ready == SDL_FALSE);
	assert(player2.score == 0);
	assert(player2.life == LIFE_MAX);

	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		assert(player2.inventory[i] == BONUS_EMPTY);
	}

	assert(player2.head_snake != NULL);
	assert(player2.head_snake->coords.x == -1);
	assert(player2.head_snake->coords.y == -1);
	assert(player2.head_snake->orientation == UP);
	assert(player2.head_snake->speed == BASE_SPEED);
	assert(player2.head_snake->skin == YELLOW);
	assert(player2.head_snake->next == NULL);

	free_players(&player1, &player2);
	// Affiche le résultat du test si tout est correct
	printf( __FILE__ " / init_players() %s\033[0m\n", assert_file ? "\033[32m[OK]" : "\033[31m[KO]");
}
