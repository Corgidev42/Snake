#ifndef APP_H
# define APP_H

# include "snake_together.h"

extern t_app	App;


/**
 * @brief Initialise l'application (SDL, TTF, fenêtre, renderer, textures,
	seed).
 *
 * Cette fonction effectue les étapes suivantes :
 * - Initialise le générateur de nombres aléatoires.
 * - Génère un seed et initialise le système de seed.
 * - Initialise SDL et vérifie son bon fonctionnement.
 * - Crée la fenêtre et le renderer.
 * - Initialise SDL_ttf pour la gestion des polices.
 * - Charge la police de caractères.
 * - Initialise les textures et les sprites.
 * - Configure les bonus disponibles.
 */
void			init_app(void);

/**
 * @brief Libère toutes les ressources et quitte proprement l'application.
 *
 * Cette fonction effectue les étapes suivantes :
 * - Ferme la police TTF et quitte le système TTF.
 * - Détruit toutes les textures SDL chargées.
 * - Détruit le renderer et la fenêtre.
 * - Quitte SDL proprement.
 */
void			kill_app(void);

/**
 * @brief Affiche un message d'erreur,
	libère les ressources et quitte le programme.
 *
 * @param message Le message d'erreur à afficher.
 *
 * Cette fonction affiche l'erreur via `SDL_Log()`, appelle `kill_app()`
 * pour libérer les ressources, puis quitte l'application avec un code d'erreur.
 */
void			SDL_ExitWithError(const char *message);

/**
 * @brief Initialise les rectangles de textures pour un type de couleur donné.
 *
 * @param color La couleur du thème à initialiser (YELLOW, BLUE, GREEN).
 *
 * Cette fonction assigne les positions et dimensions des tuiles, obstacles,
 * corps et tête du serpent pour une couleur donnée.
 */
static void		init_texture_rects_color(t_color color);

/**
 * @brief Initialise les rectangles des textures du jeu.
 *
 * Cette fonction effectue les étapes suivantes :
 * - Initialise les textures pour chaque couleur (YELLOW, BLUE, GREEN).
 * - Définit les positions et tailles des textures des pommes, bombes et bonus.
 * - Charge les fichiers de textures associés aux objets du jeu.
 */
static void		init_texture_rects(void);

#endif // APP_H
