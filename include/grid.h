#ifndef GRID_H
# define GRID_H

# include "snake_together.h" // Inclusion des dépendances nécessaires

// ------- Initialisation de la grille -------

/**
 * @brief Initialise la grille de jeu et génère les obstacles.
 *
 * @param grid Pointeur vers la structure `t_grid` à initialiser.
 *
 * Cette fonction :
 * - Alloue dynamiquement la mémoire pour la grille (`grid->cells`).
 * - Définit la position et la taille de la grille (`grid->rect_pos`).
 *
	- Initialise chaque cellule avec ses coordonnées et un type d'obstacle aléatoire.
 *
	- Génère des textures et des biomes en fonction de la carte (`get_map_color()`).
 * - Place aléatoirement des obstacles dans chaque biome.
 */
void		init_map(t_grid *grid);

// ------- Fonctions d’accès et de recherche sur la grille -------

/**

	* @brief Retourne une cellule qui est en attente d'un objet (ex : bombe ou bonus).
 *
 * @param grid Pointeur vers la structure `t_grid`.
 * @return t_cell* Pointeur vers la cellule trouvée,
	ou `NULL` si aucune n'est en attente.
 */
t_cell		*get_is_pending_cell(t_grid *grid);

/**
 * @brief Vérifie si une cellule est vide (pas d'obstacle, bonus, serpent…).
 *
 * @param cell Pointeur vers la cellule à vérifier.
 * @return SDL_bool `SDL_TRUE` si la cellule est vide, `SDL_FALSE` sinon.
 */
SDL_bool	cell_is_empty(t_cell *cell);

// ------- Génération d'entités -------

/**
 * @brief Génère un objet (bombe ou bonus) sur une cellule vide aléatoire.
 *
 * @param grid Pointeur vers la structure `t_grid`.
 * @param object_cooldown Pointeur vers le cooldown de génération d'objets.
 *
 * Cette fonction :
 * - Vérifie si un cooldown est actif avant de générer un objet.
 * - Si un objet est en attente (`is_pending`), il est généré.
 * - Sinon, elle sélectionne une cellule vide et la marque comme en attente.
 */
void		generate_object(t_grid *grid, int *object_cooldown);

/**
 * @brief Génère une pomme sur une cellule vide aléatoire.
 *
 * @param grid Pointeur vers la structure `t_grid`.
 * @param apple_cooldown Pointeur vers le cooldown de génération de pommes.
 */
void		generate_apple(t_grid *grid, int *apple_cooldown);

// ------- Sélection et gestion des cellules de la grille -------

/**
 * @brief Sélectionne une cellule vide aléatoire dans la grille.
 *
 * @param grid Pointeur vers la structure `t_grid`.
 * @param r Rayon de recherche pour garantir un espace vide autour.

	* @return t_cell* Pointeur vers la cellule sélectionnée ou `NULL` si aucune n'est disponible.
 */
t_cell		*get_rand_empty_cell(t_grid *grid, int r);

/**

	* @brief Vérifie récursivement si une zone de `r` cellules autour d'une position est vide.
 *
 * @param grid Pointeur vers la structure `t_grid`.
 * @param x Coordonnée X de la cellule à vérifier.
 * @param y Coordonnée Y de la cellule à vérifier.
 * @param r Rayon de recherche.
 * @param i Profondeur de la récursion.
 * @return SDL_bool `SDL_TRUE` si la zone est vide, `SDL_FALSE` sinon.
 */
SDL_bool	recursive_neighbourg_empty_cells(t_grid *grid, int x, int y, int r,
				int i);

// ------- Gestion des textures et biomes de la carte -------

/**

	* @brief Détermine la couleur d’une cellule en fonction de sa position sur la carte.
 *
 * @param grid Pointeur vers la structure `t_grid`.
 * @param x Coordonnée X de la cellule.
 * @param y Coordonnée Y de la cellule.
 * @return int La couleur de la cellule (`GREEN`, `YELLOW` ou `BLUE`).
 *
 * Cette fonction segmente la carte en trois zones (vert, jaune,
	bleu) et ajoute une transition fluide
 * entre elles en utilisant le paramètre `smooth` défini par le seed.
 */
int			get_map_color(t_grid *grid, int x, int y);

/**

	* @brief Génère un identifiant de tuile en fonction d'un hash basé sur les coordonnées.
 *
 * @param x Coordonnée X.
 * @param y Coordonnée Y.
 * @return int Identifiant de la tuile (entre 0 et 3).
 */
int			get_map_tile(int x, int y);

#endif // GRID_H
