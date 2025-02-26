#ifndef GAME_H
# define GAME_H

# include "snake_together.h" // Inclusion des dépendances nécessaires

/**
 * @brief Lance la fenêtre de jeu et gère la boucle principale.
 *
 * @param player1 Structure contenant les informations du premier joueur.
 * @param player2 Structure contenant les informations du second joueur.
 *
 * Cette fonction effectue les étapes suivantes :
 * - Initialise la carte (`t_grid`) et les serpents (`spawn_snake()`).
 * - Initialise la gestion du temps (`t_gametick`).
 * - Lance un compte à rebours avant le début du jeu (`countdown_transition()`).
 * - Exécute la boucle principale du jeu :
 *   - Met à jour le temps et les états (`update_gametick()`).
 *   - Gère les entrées utilisateur (`do_input()`).
 *   - Applique les animations et mouvements (`died_animation()`,
	`move_snake()`).
 *   - Effectue les actions et résout les collisions (`do_actions()`,
	`do_collision()`).
 *   - Génère les éléments interactifs (`generate_apple()`,
	`generate_object()`).
 *   - Affiche la carte,
	les serpents et l’interface utilisateur (`print_grid()`, `print_snake()`,
	etc.).
 *   - Rafraîchit le rendu (`SDL_RenderPresent()`).
 *   - Gère un délai pour maintenir un framerate stable (`SDL_Delay()`).
 *
 * La boucle s'exécute tant que :
 * - L'application est en cours (`App.running`).
 * - Les deux joueurs ont encore des vies (`player1.life` et `player2.life`).
 */
void	game_window(t_user_data player1, t_user_data player2);

#endif // GAME_H
