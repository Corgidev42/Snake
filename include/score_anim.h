#ifndef SNAKE_ANIM_H
# define SNAKE_ANIM_H

# include "snake_together.h"

/**
 * @brief Crée une nouvelle animation de score.
 *
 * @param x Position en X de l'affichage.
 * @param y Position en Y de l'affichage.
 * @param score Valeur du score à afficher.
 * @param dy_max Déplacement maximal en Y pendant la durée de vie.
 * @param life_time Durée de vie de l'animation en ms.
 * @param color Couleur du texte affiché.
 * @return t_score_anim* Un pointeur vers l'animation de score créée.
 */
t_score_anim	*create_score_anim(int x, int y, int score, int dy_max,
					int life_time, SDL_Color color);

/**
 * @brief Crée un tableau de pointeurs vers des animations de score.
 *
 * @param nb_score_anims Nombre d'animations à initialiser.
 * @return t_score_anim** Un tableau de pointeurs vers les animations de score.
 */
t_score_anim	**create_score_anims(int nb_score_anims);

/**
 * @brief Détruit une animation de score.
 *
 * @param score_anim Pointeur vers l'animation à détruire.
 */
void			destroy_score_anim(t_score_anim *score_anim);

/**
 * @brief Détruit toutes les animations de score et libère la mémoire.
 *
 * @param score_anims Tableau de pointeurs vers les animations.
 */
void			destroy_score_anims(t_score_anim **score_anims);

/**
 * @brief Supprime une animation de score du tableau et ajuste les indices.
 *
 * @param score_anims Tableau des animations de score.
 * @param score_anim Animation spécifique à retirer.
 */
void			remove_score_anim(t_score_anim **score_anims,
					t_score_anim *score_anim);

/**
 * @brief Ajoute une animation de score dans le tableau des animations.
 *
 * @param score_anims Tableau des animations de score.
 * @param score_anim Animation à ajouter.
 */
void			add_score_anim(t_score_anim **score_anims,
					t_score_anim *score_anim);

/**
 * @brief Met à jour toutes les animations de score en fonction du temps écoulé.
 *
 * @param score_anims Tableau des animations de score.
 * @param elapsed_time Temps écoulé depuis la dernière mise à jour.
 */
void			update_score_anims(t_score_anim **score_anims,
					int elapsed_time);

/**
 * @brief Ajoute une animation de score indiquant la taille du serpent.
 *
 * @param score_anims Tableau des animations de score.
 * @param player Joueur auquel ajouter l'animation.
 */
void			add_snake_size_score_anim(t_score_anim **score_anims,
					t_user_data *player);

/**

	* @brief Gère l'affichage du score basé sur la taille du serpent à intervalle régulier.
 *
 * @param score_snake_size_cooldown Temps avant la prochaine animation de score.
 * @param player1 Joueur 1.
 * @param player2 Joueur 2.
 * @param score_anims Tableau des animations de score.
 */
void			do_score_snake_size(int *score_snake_size_cooldown,
					t_user_data *player1, t_user_data *player2,
					t_score_anim **score_anims);

/**
 * @brief Ajoute une animation de score au niveau de la tête du serpent.
 *
 * @param score_anims Tableau des animations de score.
 * @param head_snake Tête du serpent où afficher l'animation.
 * @param score Valeur du score à afficher.
 * @param color_type Type de couleur de l'affichage.
 */
void			add_snake_score_anim(t_score_anim **score_anims,
					t_snake_part *head_snake, int score, t_color color_type);

/**
 * @brief Affiche toutes les animations de score à l'écran.
 *
 * @param score_anims Tableau des animations de score.
 * @param renderer Renderer SDL pour l'affichage.
 * @param font Police d'écriture utilisée.
 */
void			print_score_anims(t_score_anim **score_anims,
					SDL_Renderer *renderer, TTF_Font *font);

#endif // SNAKE_TOGETHER_H
