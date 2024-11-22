#ifndef APP_H
# define APP_H

#include "structs.h"

t_app	App;

/**
 * @brief Initialise l'application (window, renderer, running).
 */
void	init_app(void);

/**
 * @brief Libère la mémoire avant de fermer le programme.
 */
void	kill_app(void);

#endif
