#ifndef GAMETICK_H
# define GAMETICK_H

# include "snake_together.h" // Inclusion des dépendances nécessaires

/**

	* @brief Initialise la structure `t_gametick` pour gérer les chronomètres du jeu.
 *
 * @param gametick Pointeur vers la structure `t_gametick` à initialiser.
 *
 * Cette fonction effectue les initialisations suivantes :
 * - Définit le temps initial (`elapsed_time`).
 * - Configure les délais de génération (`apple_cooldown`, `object_cooldown`).
 *
	- Initialise les délais de déplacement et de vitesse des serpents (`snake_X_cooldown`).
 * - Gère les délais des effets (`snake_X_star_cooldown`,
	`snake_X_slow_cooldown`).
 *
	- Initialise les animations (`snakes_animation`) et les délais de mort (`snake_X_died_cooldown`).
 * - Définit un temps d'attente avant le début de la partie (`timer`).
 */
void	init_gametick(t_gametick *gametick);

/**

	* @brief Met à jour les délais et chronomètres du jeu en fonction du temps écoulé.
 *

	* @param gametick Pointeur vers la structure `t_gametick` contenant les chronomètres.
 * @param player1 Pointeur vers la structure `t_user_data` du premier joueur.
 * @param player2 Pointeur vers la structure `t_user_data` du second joueur.
 *
 * Cette fonction met à jour les éléments suivants :
 * - Diminue les délais de génération (`apple_cooldown`, `object_cooldown`).
 *
	- Gère les délais de déplacement des serpents en fonction de leur vitesse et des ralentissements (`snake_X_cooldown`).
 * - Met à jour les cooldowns des effets (`snake_X_star_cooldown`,
	`snake_X_slow_cooldown`).
 *
	- Réduit les délais de mort (`snake_X_died_cooldown`) si un serpent est en état `BONKED`.
 *
	- Met à jour le temps restant pour l'animation des serpents (`snakes_animation`).
 * - Rafraîchit le temps écoulé (`elapsed_time`) pour le prochain appel.
 */
void	update_gametick(t_gametick *gametick, t_user_data *player1,
			t_user_data *player2);

#endif // GAMETICK_H
