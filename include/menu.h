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
void	do_input(t_user_data *player1, t_user_data *player);

/**
 * @brief Affiche le choix du joueur 1 dans le menu.
 *
 * @param player1 Données du joueur 1.
 * @param rect_left Rectangle de la zone d'affichage pour le joueur.
 */

#endif
