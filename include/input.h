#ifndef INPUT_H
# define INPUT_H

# include "snake_together.h"

/**
 * @brief Gère les entrées utilisateur pendant le jeu.
 *
 * Cette fonction écoute les événements clavier et souris pour gérer les mouvements
 * et actions des joueurs (rotation du serpent, utilisation des bonus, etc.).
 *
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.
 */
void	do_input(t_user_data *player1, t_user_data *player2);

/**
 * @brief Gère les entrées utilisateur dans le menu principal.
 *
 * Permet aux joueurs de modifier leur apparence, de signaler qu'ils sont prêts,
 * et d'utiliser des raccourcis pour tester des bonus.
 *
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.
 */
void	menu_do_input(t_user_data *player1, t_user_data *player2);

#endif /* INPUT_H */
