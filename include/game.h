#ifndef GAME_H
# define GAME_H

# include "snake.h"

void	free_all_game(t_grid grid);

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
void	update_gametick(t_gametick *gametick, int speed1, int speed2);

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
 * @brief Affiche l'état actuel de la grille de jeu avec tous les objets.
 *
 * Cette fonction prend une structure t_grid en entrée et affiche la grille
 * sur la sortie standard. La grille représente la zone de jeu où le serpent
 * se déplace, où la nourriture est placée, ainsi que les bonus et autres objets.
 * L'affichage est basé sur l'état des valeurs dans la structure t_grid.
 *
 * @param grid La grille de jeu à afficher.
 */
void	print_grid(t_grid grid, t_gametick gametick);

/**
 * @brief Affiche le serpent sur la carte.
 *
 * @param grid Grille de jeu.
 * @param player Données du joueur.
 */
void	print_snake(t_grid grid, t_snake_part *head_snake);

void	print_obstacles(t_grid grid);

/**
 * @brief Affiche le tableau des scores en haut.
 *
 * @param player1 Données du joueur 1.
 * @param player2 Données du joueur 2.
 */
void	print_scoreboard(SDL_Rect rect_pos,t_user_data player1, t_user_data player2);

#endif
