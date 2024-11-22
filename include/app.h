#ifndef APP_H
# define APP_H

#include "struct.h"

t_app	App;

//Initialise l'application (window, renderer, running)
void	init_app(void);
//Libere la memoire avant de fermer le programme
void	kill_app(void);

#endif
