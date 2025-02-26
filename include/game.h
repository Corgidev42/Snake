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
void				game_window(t_user_data player1, t_user_data player2);

/**
 * @brief Retourne la couleur associée à un skin de serpent.
 *
 * Cette fonction associe une couleur spécifique à chaque skin de serpent.
 * Si le skin ne correspond à aucune couleur définie,
	la couleur blanche est retournée par défaut.
 *
 * @param color La couleur associée au skin du serpent.
 * @return SDL_Color La couleur correspondante en SDL.
 */
static SDL_Color	get_color_by_skin(t_color color);

/**
 * @brief Affiche l'écran de fin de partie.
 *
 * Cette fonction affiche le joueur gagnant,
	la taille maximale atteinte par chaque serpent,
 * le score final de chaque joueur, et attend une entrée pour quitter l'écran.
 *
 * - Affiche le joueur gagnant ou "Draw" en cas d'égalité.
 *
	- Affiche les scores et tailles maximales des serpents avec des icônes correspondantes.
 * - Attend une entrée clavier pour fermer l'écran de fin de partie.
 *
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.
 */
void				end_game_window(t_user_data *player1, t_user_data *player2);

#endif // GAME_H
