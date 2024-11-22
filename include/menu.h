#ifndef MENU_H
# define MENU_H

# include "structs.h"

/**
 * @brief Fonction principale qui gère le menu.
 *
 * @param player1 Pointeur vers les données du joueur 1.
 * @param player2 Pointeur vers les données du joueur 2.
 */
void	menu_window(t_user_data *player1, t_user_data *player2);

/**
 * @brief Gère les entrées des joueurs dans le menu.
 *
 * @param player1 Pointeur vers les données du joueur 1.
 * @param player2 Pointeur vers les données du joueur 2.
 */
void	do_input(t_user_data *player1, t_user_data *player2);

/**
 * @brief Affiche le choix du joueur 1 dans le menu.
 *
 * @param player1 Données du joueur 1.
 * @param rect_left Rectangle de la zone d'affichage pour le joueur 1.
 */
void	render_player_choice(t_user_data player1, SDL_Rect rect_left);

/**
 * @brief Affiche le choix du joueur 2 dans le menu.
 *
 * @param player2 Données du joueur 2.
 * @param rect_right Rectangle de la zone d'affichage pour le joueur 2.
 */
void	render_player_choice(t_user_data player2, SDL_Rect rect_right);

#endif
