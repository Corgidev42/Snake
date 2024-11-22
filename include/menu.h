#ifndef MENU_H
# define MENU_H

# include "structs.h"

//Fonction principal qui gere le menu
void	menu_window(t_user_data *player1, t_user_data *player2);

void	do_input(t_user_data *player1, t_user_data *player2);

void	render_player_choice(t_user_data player1, SDL_Rect rect_left);
void	render_player_choice(t_user_data player2, SDL_Rect rect_right);

#endif
