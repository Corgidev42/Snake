#ifndef GAME_H
# define GAME_H

# include "structs.h"

/**
 * @brief Fonction principale qui gère le jeu.
 *
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 */
void	game_window(t_user_data player1, t_user_data player2);

/**
 * @brief Initialise la carte en laissant un espace en haut.
 *
 * @param grid Pointeur vers la grille de jeu.
 */
void	init_map(t_grid *grid);

/**
 * @brief Fait apparaître la tête du serpent sur la carte.
 *
 * @param grid Grille de jeu.
 * @param head_snake Tête du serpent.
 */
void	spawn_snake(t_grid grid, t_snake_part *head_snake);

/**
 * @brief Initialise les paramètres de temps pour la gestion du temps de tous les événements,
 * il va s'occuper des cooldown des pommes et des objets.
 *
 * @param gametick Pointeur vers la structure de gestion du temps de jeu.
 */
void	init_gametick(t_gametick *gametick);

/**
 * @brief Gère les entrées des joueurs.
 *
 * @param player1 Pointeur vers les données du joueur 1.
 * @param player2 Pointeur vers les données du joueur 2.
 */
void	do_input(t_user_data *player1, t_user_data *player2);

/**
 * @brief Déplace le serpent d'un joueur.
 *
 * @param snake_cooldown Cooldown du serpent.
 * @param head_snake Tête du serpent.
 */
void	move_snake(int *snake_cooldown, t_snake_part *head_snake);

/**
 * @brief Gère les collisions entre les joueurs et les obstacles.
 *
 * @param grid Grille de jeu.
 * @param player1 Pointeur vers les données du joueur 1.
 * @param player2 Pointeur vers les données du joueur 2.
 */
void	do_collision(t_grid grid, t_user_data *player1, t_user_data *player2);

/**
 * @brief Met à jour les paramètres de temps de jeu en fonction des actions des joueurs.
 *
 * @param gametick Pointeur vers la structure de gestion du temps de jeu.
 */
void	update_gametick(t_gametick *gametick);

/**
 * @brief Génère une pomme sur la carte.
 *
 * @param grid Pointeur vers la grille de jeu.
 * @param apple_cooldown Cooldown de la pomme.
 */
void	generate_apple(t_grid *grid, int *apple_cooldown);

/**
 * @brief Génère un objet (Bonus ou Bombe) sur la carte.
 *
 * @param grid Pointeur vers la grille de jeu.
 * @param object_cooldown Cooldown de l'objet.
 */
void	generate_object(t_grid *grid, int *object_cooldown);

/**
 * @brief Affiche le serpent sur la carte.
 *
 * @param grid Grille de jeu.
 * @param player Données du joueur.
 */
void	print_snake(t_grid grid, t_user_data player);

/**
 * @brief Affiche les objets (Bonus, Pomme et Bombe) sur la carte.
 *
 * @param grid Grille de jeu.
 */
void	print_objets(t_grid grid);

/**
 * @brief Affiche le tableau des scores en haut.
 *
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 */
void	print_scoreboard(t_user_data player1, t_user_data player2);

#endif