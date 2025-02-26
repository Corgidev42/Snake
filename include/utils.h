#ifndef UTILS_H
# define UTILS_H

# include "snake_together.h"

/**
 * @brief Récupère la largeur d'un texte en pixels.
 *
 * @param text Chaîne de caractères dont on veut connaître la largeur.
 * @param font Police utilisée pour le rendu du texte.
 * @return int Largeur du texte en pixels.
 *
 * Cette fonction utilise `TTF_SizeText()` pour déterminer la largeur
 * du texte avec la police spécifiée. En cas d'erreur, le programme
 * quitte en appelant `SDL_ExitWithError()`.
 */
int			get_text_width(const char *text, TTF_Font *font);

/**
 * @brief Récupère la hauteur d'un texte en pixels.
 *
 * @param text Chaîne de caractères dont on veut connaître la hauteur.
 * @param font Police utilisée pour le rendu du texte.
 * @return int Hauteur du texte en pixels.
 *
 * Utilise `TTF_SizeText()` pour récupérer la hauteur du texte.
 * En cas d'erreur, le programme quitte en appelant `SDL_ExitWithError()`.
 */
int			get_text_height(const char *text, TTF_Font *font);

/**
 * @brief Affiche un texte à l'écran.
 *
 * @param renderer Le renderer SDL utilisé pour dessiner le texte.
 * @param text Le texte à afficher.
 * @param rect La position et la taille du texte à l'écran.
 * @param font La police utilisée pour le rendu.
 * @param color La couleur du texte (SDL_Color).
 *

	* Cette fonction génère une texture à partir du texte fourni et la rend à l'écran.
 * - Utilise `TTF_RenderText_Solid()` pour créer une surface.
 * - Convertit la surface en texture SDL.
 * - Affiche la texture aux coordonnées spécifiées.
 * - Libère la texture après affichage.
 *
 * En cas d'erreur (surface ou texture introuvable),
	`SDL_ExitWithError()` est appelé.
 */
void		render_text(SDL_Renderer *renderer, const char *text, SDL_Rect rect,
				TTF_Font *font, SDL_Color color);

/**
 * @brief Charge une texture depuis un fichier image.
 *
 * @param path Le chemin du fichier image.
 * @return SDL_Texture* Pointeur vers la texture SDL créée.
 *

	* Cette fonction charge une image depuis un fichier et la convertit en texture SDL.
 * - Utilise `IMG_Load()` pour charger l'image en surface.
 * - Convertit la surface en texture avec `SDL_CreateTextureFromSurface()`.
 * - Libère la surface après conversion.
 *
 * En cas d'échec lors du chargement ou de la création de la texture,
	le programme quitte via `SDL_ExitWithError()`.
 */
SDL_Texture	*load_texture(const char *path);

#endif // UTILS_H
