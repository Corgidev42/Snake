#ifndef GAME_LOGIC_H
# define GAME_LOGIC_H

# include "snake_together.h"

/**
 * @brief Ajoute un bonus à l'inventaire du joueur.
 *
 * Ajoute un bonus dans le premier slot vide de l'inventaire du joueur.
 * Le bonus TP (téléportation) est toujours ajouté en priorité au second slot.
 *
 * @param player Les données du joueur.
 * @param bonus Le bonus à ajouter.
 */
void		add_inventory_bonus(t_user_data *player, t_bonus bonus);

/**
 * @brief Active l'effet de vitesse si le joueur possède des pommes de vitesse.
 *
 * Si le joueur possède au moins une pomme de vitesse,
	la vitesse du serpent est augmentée.
 *
 * @param player Les données du joueur.
 */
void		handle_speed(t_user_data *player);

/**
 * @brief Supprime un bonus de l'inventaire du joueur.
 *
 * Si le bonus supprimé est dans le premier slot,
	le second slot est déplacé en premier slot.
 *
 * @param player Les données du joueur.
 * @param slot L'index du slot à supprimer (0 ou 1).
 */
void		remove_bonus_slot(t_user_data *player, int slot);

/**
 * @brief Active l'effet du bonus stocké dans l'inventaire du joueur.
 *
 * Applique l'effet du bonus et le supprime de l'inventaire après activation.
 *
 * @param player Les données du joueur.
 */
void		handle_bonus(t_user_data *player);

/**
 * @brief Gère les actions et effets actifs des joueurs à chaque tick de jeu.
 *

	* Cette fonction met à jour les effets liés aux bonus et à la vitesse pour chaque joueur.
 *
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.

	* @param gametick Structure contenant les cooldowns et autres données liées au temps de jeu.
 */
void		do_actions(t_user_data *player1, t_user_data *player2,
				t_gametick *gametick);

/**

	* @brief Gère les collisions et interactions entre les serpents et leur environnement.
 *
 * Cette fonction vérifie les collisions des serpents avec les obstacles,
	les bombes,
 * et les autres serpents. Elle met également à jour le score et l'inventaire
 * en fonction des objets ramassés.
 *
 * @param grid La grille de jeu.
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.
 * @param score_anims Tableau des animations de score.
 */
void		do_collision(t_grid *grid, t_user_data *player1,
				t_user_data *player2, t_score_anim **score_anims);

/**
 * @brief Gère les collisions fatales pour les serpents.
 *
 * Vérifie si un serpent heurte un mur, une bombe,
	son propre corps ou l'autre serpent.
 * En cas de collision,
	le serpent subit les conséquences correspondantes (perte de vie,
	suppression de parties).
 *
 * @param grid La grille de jeu.
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.
 * @param score_anims Tableau des animations de score.
 */
void		kill_collision(t_grid *grid, t_user_data *player1,
				t_user_data *player2, t_score_anim **score_anims);

/**
 * @brief Gère les collisions liées au score.
 *

	* Vérifie si un serpent ramasse une pomme ou un bonus et met à jour son score et son inventaire en conséquence.
 *
 * @param grid La grille de jeu.
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.
 * @param score_anims Tableau des animations de score.
 */
void		score_collision(t_grid *grid, t_user_data *player1,
				t_user_data *player2, t_score_anim **score_anims);

/**
 * @brief Vérifie si un serpent occupe une certaine position sur la grille.
 *
 * @param head_snake Pointeur vers la tête du serpent.
 * @param coords Coordonnées à vérifier.
 * @return SDL_TRUE si un serpent est présent à ces coordonnées,
	SDL_FALSE sinon.
 */
SDL_bool	has_snake_in_coords(t_snake_part *head_snake, t_coords coords);

/**

	* @brief Vérifie si la queue d'un serpent occupe une certaine position sur la grille.
 *
 * Cette fonction ignore la tête du serpent et ne vérifie que le corps.
 *
 * @param head_snake Pointeur vers la tête du serpent.
 * @param coords Coordonnées à vérifier.
 * @return SDL_TRUE si la queue du serpent est présente à ces coordonnées,
	SDL_FALSE sinon.
 */
SDL_bool	has_snake_tail_in_coords(t_snake_part *head_snake, t_coords coords);

/**
 * @brief Vérifie si deux serpents sont face à face.
 *
 * Cette fonction compare l'orientation des têtes des serpents pour déterminer
 * s'ils se dirigent directement l'un vers l'autre.
 *
 * @param head_snake_1 Pointeur vers la tête du premier serpent.
 * @param head_snake_2 Pointeur vers la tête du second serpent.
 * @return SDL_TRUE si les serpents sont face à face, SDL_FALSE sinon.
 */
SDL_bool	are_snakes_facing(t_snake_part *head_snake_1,
				t_snake_part *head_snake_2);

/**
 * @brief Effectue un rollback du mouvement du serpent.
 *
 * Cette fonction ajoute une partie à l'arrière du serpent et retire une partie
 * de la tête si la taille du serpent est supérieure à deux. Cela permet
 * d'inverser un mouvement récent.
 *
 * @param grid La grille de jeu.
 * @param player Les données du joueur.
 */
void		do_rollback_move(t_grid *grid, t_user_data *player);

/**
 * @brief Gère une collision en appliquant un état de "BONK".
 *
 * Lorsqu'un serpent subit un choc, il effectue un rollback de mouvement,
 * sa vitesse est réduite à zéro, et son état est mis à BONKED.
 *
 * @param grid La grille de jeu.
 * @param player Les données du joueur.
 */
void		colls_to_bonk(t_grid *grid, t_user_data *player);

/**
 * @brief Joue l'animation de mort du serpent.
 *
 * À chaque tick, si le cooldown est terminé,
	une partie du corps du serpent est retirée,
 * sauf si le joueur est sous l'effet du bonus STAR.
 *
 * @param grid La grille de jeu.
 * @param died_cooldown Cooldown pour limiter la vitesse d'animation.
 * @param player Les données du joueur.
 */
void		died_animation(t_grid *grid, int *died_cooldown,
				t_user_data *player);

#endif /* GAME_LOGIC_H */
