#ifndef SNAKE_H
# define SNAKE_H

# include "snake_together.h"

/**
 * @brief Spawn un serpent sur la grille.
 *
 * Cette fonction place un serpent sur une cellule vide aléatoire et initialise
 * ses paramètres de vitesse et d'orientation.
 *
 * @param grid La grille de jeu.
 * @param player Les données du joueur associées au serpent.
 */
void			spawn_snake(t_grid *grid, t_user_data *player);

/**
 * @brief Ajoute une nouvelle partie du corps du serpent à l'arrière.
 *

	* La nouvelle partie est ajoutée en fonction de l'orientation actuelle du serpent.
 *
 * @param head_snake Le pointeur vers la tête du serpent.
 * @return Un pointeur vers la nouvelle partie du serpent.
 */
t_snake_part	*add_behind_snake_part(t_snake_part *head_snake);

/**
 * @brief Supprime la dernière partie du serpent.
 *
 * Si le serpent n'a plus de corps,
	le joueur perd une vie et un nouveau serpent est spawn.
 *
 * @param grid La grille de jeu.
 * @param player Les données du joueur associées au serpent.
 */
void			remove_behind_snake_part(t_grid *grid, t_user_data *player);

/**

	* @brief Supprime un certain nombre de parties du corps du serpent en partant de la tête.
 *
 * Si le nombre de suppressions dépasse la taille du serpent,
	le joueur perd une vie et
 * un nouveau serpent est spawn.
 *
 * @param grid La grille de jeu.
 * @param player Les données du joueur associées au serpent.
 * @param nb_removes Le nombre de parties à supprimer.
 */
void			remove_snake_head_parts(t_grid *grid, t_user_data *player,
					int nb_removes);

/**
 * @brief Tue entièrement le serpent.
 *
 * Supprime toutes les parties du serpent et libère la mémoire associée.
 *
 * @param grid La grille de jeu.
 * @param player Les données du joueur associées au serpent.
 */
void			kill_snake(t_grid *grid, t_user_data *player);

/**
 * @brief Change l'orientation du serpent.
 *

	* Empêche les rotations à 180° pour éviter que le serpent ne se retourne directement.
 *
 * @param player Les données du joueur associées au serpent.
 * @param orientation La nouvelle orientation du serpent.
 */
void			rotate_snake(t_user_data *player, t_orientation orientation);

/**
 * @brief Déplace le serpent d'une case dans la direction actuelle.
 *
 * Cette fonction met à jour la position de chaque partie du corps du serpent,
 * applique les effets de téléportation si le joueur possède l'objet TP,
 * et met à jour la grille de jeu.
 *
 * @param grid La grille de jeu.
 * @param snake_cooldown Le cooldown du mouvement du serpent.
 * @param player Les données du joueur associées au serpent.
 */
void			move_snake(t_grid *grid, int *snake_cooldown,
					t_user_data *player);

/**
 * @brief Retourne la taille actuelle du serpent.
 *
 * @param head_snake Le pointeur vers la tête du serpent.
 * @return La taille du serpent.
 */
int				get_size_snake(t_snake_part *head_snake);

#endif /* SNAKE_H */
