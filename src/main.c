#include "snake_together.h"

t_app App;

/*
	Au demarrage, timer de lancement de la partie

	Scores a update
	Fin de partie

	!!!!!! IMPORTANT !!!!!!
	STRUCTURER LE CODE
	TOUS LES SEGFAULTS
	TOUS LES FREES
	FAIRE LES TESTS

	V3 - A faire sur du CPP !!!!!!
	!!!! PENSER LE CODE EN RESEAU LOCAL
	Transition entre les menus
	Animations des snakes quand ils meurent (bonk + explosion de la queue a la tete avant de respawn)
	mettre les animation de bombe + aoe , mettre les missiles et la mine
	dans le menu, rendre certain bonus activable

	Ajouter des sons
	A tester -> Ligne de demarcation entre biomes

	Marge sur la map avec background (v3)
	Ajouter une video dans le menu
	score update sur la map ( on voit les scores des joueurs sur la map )
	ameliorer l'esthethique de la barre de vitesse et les objets
	ameliorer le fond du menu

	V4
	Reseau local

	V5
	Mode online (serveur + client)
	map gigantesque (a la sleether.io)
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
