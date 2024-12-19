#ifndef APP_H
# define APP_H

#include "snake.h"

extern t_app	App;

/**
 * @brief Initialise l'application (window, renderer, running).
 */
void	init_app(void);

/**
 * @brief Libère la mémoire avant de fermer le programme.
 */
void	kill_app(void);


void	SDL_ExitWithError(const char *message);
#endif
