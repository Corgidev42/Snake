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
 * @brief Affiche le choix du joueur dans le menu.
 *
 * @param rect_side Rectangle de la zone d'affichage pour le joueur.
 * @param player Données du joueur.
 */
void	print_player_choice(SDL_Rect rect_side, t_user_data player);

#endif
