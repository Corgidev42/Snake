#ifndef PLAYER_H
# define PLAYER_H

# include "snake_together.h"

// ------- Initialisation des joueurs -------

/**
 * @brief Initialise les structures des deux joueurs.
 *
 * @param player1 Pointeur vers la structure `t_user_data` du premier joueur.
 * @param player2 Pointeur vers la structure `t_user_data` du second joueur.
 *
 * Cette fonction effectue les opérations suivantes :
 * - Initialise les statistiques de chaque joueur (`id`, `score`, `life`, etc.).
 * - Définit les valeurs par défaut pour les états (`is_speed`, `is_star`,
	`is_slow`).
 * - Alloue dynamiquement la mémoire pour la tête du serpent de chaque joueur.
 * - Initialise les coordonnées,
	l’orientation et la couleur de départ du serpent.
 * - Remplit l’inventaire des joueurs avec des cases vides (`BONUS_EMPTY`).
 *
 * En cas d’échec d’allocation de mémoire pour le serpent,
	le programme s’arrête (`exit(1)`).
 */
void	init_players(t_user_data *player1, t_user_data *player2);

// ------- Libération des joueurs -------

/**
 * @brief Libère la mémoire allouée pour les serpents des joueurs.
 *
 * @param player1 Pointeur vers la structure `t_user_data` du premier joueur.
 * @param player2 Pointeur vers la structure `t_user_data` du second joueur.
 *
 * Cette fonction :
 * - Parcourt la liste chaînée du serpent de chaque joueur et libère la mémoire.
 * - Réinitialise le pointeur de tête de serpent à `NULL` après la libération.
 */
void	free_players(t_user_data *player1, t_user_data *player2);

#endif // PLAYER_H
