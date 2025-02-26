#ifndef MENU_H
# define MENU_H

# include "snake_together.h"

/**
 * @brief Affiche les choix du joueur dans le menu.
 *
 * Cette fonction affiche l'identifiant du joueur, la couleur de son serpent,
 * et son statut de préparation (READY ou non). Elle affiche aussi les touches
 * pour changer de couleur et valider son choix.
 *
 * @param rect_side Rectangle de positionnement de l'affichage.
 * @param player Les données du joueur.
 */
void	print_player_choice(SDL_Rect rect_side, t_user_data player);

/**
 * @brief Affiche les choix de bonus disponibles.
 *
 * Cette fonction affiche les icônes des bonus disponibles et les touches associées
 * pour les sélectionner (1, 2, 3, 4). Si un bonus n'est pas disponible, une croix
 * est affichée par-dessus.
 *
 * @param rect Rectangle de positionnement de l'affichage.
 */
void	print_bonus_choice(SDL_Rect rect);

/**
 * @brief Gère l'affichage et la logique du menu de sélection.
 *
 * Cette fonction affiche les écrans de sélection des joueurs et du bonus, et attend
 * que les deux joueurs soient prêts avant de démarrer la partie.
 *
 * @param player1 Données du premier joueur.
 * @param player2 Données du second joueur.
 */
void	menu_window(t_user_data *player1, t_user_data *player2);

/**
 * @brief Recherche l'index d'un bonus dans la liste des bonus disponibles.
 *
 * @param bonus Le bonus recherché.
 * @return L'index du bonus s'il est trouvé, -1 sinon.
 */
int	find_bonus_index(t_bonus bonus);

/**
 * @brief Active ou désactive un bonus dans la liste des bonus disponibles.
 *
 * Si le bonus n'est pas présent, il est ajouté. S'il est déjà présent, il est supprimé.
 *
 * @param bonus Le bonus à activer ou désactiver.
 */
void	handle_bonus_active(t_bonus bonus);

#endif /* MENU_H */
