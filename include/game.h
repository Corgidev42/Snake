#ifndef GAME_H
# define GAME_H

# include "structs.h"

/**
 * @brief Fonction principale qui gère le jeu.
 *
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 */
void game_window(t_user_data player1, t_user_data player2);

/**
 * @brief Initialise la carte en laissant un espace en haut.
 *
 * @param grid Pointeur vers la grille de jeu.
 */
void init_map(t_grid *grid);

/**
 * @brief Fait apparaître les serpents sur la carte.
 *
 * @param grid Grille de jeu.
 * @param headsnake_1 Tête du serpent 1.
 * @param headsnake_2 Tête du serpent 2.
 */
void spawn_snake(t_grid grid, t_snake_part headsnake_1, t_snake_part headsnake_2);

/**
 * @brief Initialise les paramètres de jeu.
 *
 * @param gametick Pointeur vers la structure de gestion du temps de jeu.
 */
void init_gametick(t_gametick *gametick);

/**
 * @brief Gère les entrées des joueurs.
 *
 * @param player1 Pointeur vers les données du joueur 1.
 * @param player2 Pointeur vers les données du joueur 2.
 */
void do_input(t_user_data *player1, t_user_data *player2);

/**
 * @brief Déplace le serpent d'un joueur.
 *
 * @param player Données du joueur.
 */
void move_snake(t_user_data player);

/**
 * @brief Gère les collisions entre les joueurs et les obstacles.
 *
 * @param grid Grille de jeu.
 * @param player1 Pointeur vers les données du joueur 1.
 * @param player2 Pointeur vers les données du joueur 2.
 */
void do_collision(t_grid grid, t_user_data *player1, t_user_data *player2);

/**
 * @brief Met à jour les paramètres de jeu.
 *
 * @param gametick Pointeur vers la structure de gestion du temps de jeu.
 */
void update_gametick(t_gametick *gametick);

/**
 * @brief Génère une pomme sur la carte.
 *
 * @param grid Grille de jeu.
 * @param gametick Structure de gestion du temps de jeu.
 */
void generate_apple(t_grid grid, t_gametick gametick);

/**
 * @brief Génère un objet sur la carte.
 *
 * @param grid Grille de jeu.
 * @param gametick Structure de gestion du temps de jeu.
 */
void generate_object(t_grid grid, t_gametick gametick);

/**
 * @brief Affiche le serpent sur la carte.
 *
 * @param grid Grille de jeu.
 * @param player Données du joueur.
 */
void print_snake(t_grid grid, t_user_data player);

/**
 * @brief Affiche les objets sur la carte.
 *
 * @param grid Grille de jeu.
 */
void print_objets(t_grid grid);

/**
 * @brief Affiche le tableau des scores.
 *
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 */
void print_scoreboard(t_user_data player1, t_user_data player2);

#endif
