#include "snake.h"

t_app App;

/*
	A tester -> Ligne de demarcation entre biomes
	Scores a update
	Animation des bombes
	Ajouter les bonus
	Gerer les AOE des bombes
	Speed
	Fin de partie
	Makefile
	Is pending en mode beau
	
	!!!!!! IMPORTANT !!!!!!
	STRUCTURER LE CODE
	TOUS LES SEGFAULTS
	TOUS LES FREES
	FAIRE LES TESTS

	V3
	Ajouter des sons
	Animations des snakes quand ils meurent (bonk + explosion de la queue a la tete avant de respawn)
	Marge sur la map avec background (v3)
	Ajouter une video dans le menu
	Transition entre les menus
	Au demarrage, timer de lancement de la partie
*/

int	main(int argc, char const *argv[])
{
	t_user_data	player1;
	t_user_data	player2;

	init_app();
	while (App.running)
	{
		init_players(&player1, &player2);
		menu_window(&player1, &player2);
		game_window(player1, player2);
	}
	free_players(&player1, &player2);
	kill_app();
	return (0);
}
