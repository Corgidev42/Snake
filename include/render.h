#ifndef RENDER_H
# define RENDER_H

# include "snake_together.h"

// ------- Rendu de la grille, obstacles, bonus -------

/**
 * @brief Affiche la grille de jeu avec les textures associées.
 *
 * @param grid Grille de jeu contenant les cellules et leurs propriétés.
 *
 * Cette fonction :
 *
	- Affiche les cases de la grille en fonction de leur texture et de leur position.
 * - Dessine les pommes,
	les bombes et les bonus s'ils sont présents dans une cellule.
 */
void	print_grid(t_grid grid);

/**
 * @brief Affiche les obstacles présents sur la grille.
 *
 * @param grid Grille de jeu contenant les cellules et leurs obstacles.
 *
 * Cette fonction :
 * - Parcourt toutes les cellules de la grille.
 * - Affiche les textures des obstacles si une cellule en contient.
 */
void	print_obstacles(t_grid grid);

/**

	* @brief Affiche un compte à rebours sur une cellule où un objet est en attente.
 *
 * @param grid Grille de jeu.
 * @param object_cooldown Temps restant avant l'apparition de l'objet.
 *
 * Cette fonction :
 * - Trouve la cellule marquée comme "pending".
 * - Affiche un texte avec le temps restant avant son apparition.
 */
void	print_is_pending(t_grid grid, int object_cooldown);

// ------- Rendu des serpents -------

/**
 * @brief Affiche un serpent sur la grille.
 *
 * @param grid Grille de jeu.
 * @param head_snake Pointeur vers la tête du serpent.
 * @param snake_animation Indice de l'animation actuelle du serpent.
 *
 * Cette fonction :
 * - Affiche la tête du serpent avec l'animation correspondante.
 * - Affiche le corps du serpent en reliant correctement ses segments.
 */
void	print_snake(t_grid grid, t_snake_part *head_snake, int snake_animation);

// ------- Rendu de l’interface (scoreboard, jauges, actions) -------

/**
 * @brief Affiche les actions disponibles et les jauges de vitesse des joueurs.
 *
 * @param rect_pos Position du cadre des actions.
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 *
 * Cette fonction :
 * - Affiche les jauges de vitesse en fonction du nombre de pommes mangées.
 * - Affiche les bonus en possession de chaque joueur.
 */
void	print_actions(SDL_Rect rect_pos, t_user_data player1,
			t_user_data player2);

/**
 * @brief Affiche le tableau des scores avec les informations des joueurs.
 *
 * @param rect_pos Position du scoreboard.
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 *
 * Cette fonction :
 * - Affiche le nom des catégories ("Player", "Score", "Life").
 * - Affiche les valeurs correspondantes aux joueurs.
 */
void	print_scoreboard(SDL_Rect rect_pos, t_user_data player1,
			t_user_data player2);

// ------- Rendu du compte à rebours -------

/**
 * @brief Affiche une transition de début de partie avec un compte à rebours.
 *
 * @param grid Grille de jeu.
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 * @param gametick Pointeur vers la structure de gestion du temps de jeu.
 * @param actions_rect_pos Position du cadre des actions.
 * @param scoreboard_rect_pos Position du tableau des scores.
 *
 * Cette fonction :
 * - Affiche un compte à rebours centré à l'écran avant le début de la partie.
 * - Maintient l'affichage du plateau de jeu pendant la transition.
 */
void	countdown_transition(t_grid grid, t_user_data player1,
			t_user_data player2, t_gametick *gametick,
			SDL_Rect actions_rect_pos, SDL_Rect scoreboard_rect_pos);

#endif // RENDER_H
