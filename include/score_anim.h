#ifndef SCORE_ANIM_H
# define SCORE_ANIM_H

# include "snake_together.h"

t_score_anim	*create_score_anim(int x, int y, int score, int dy_max, int life_time, SDL_Color color);
t_score_anim	**create_score_anims(int nb_score_anims);
void			destroy_score_anim(t_score_anim *score_anim);
void			destroy_score_anims(t_score_anim **score_anims);
void			remove_score_anim(t_score_anim **score_anims, t_score_anim *score_anim);
void			add_score_anim(t_score_anim **score_anims, t_score_anim *score_anim);
void			update_score_anims(t_score_anim **score_anims, int elapsed_time);
void			add_snake_size_score_anim(t_score_anim **score_anims, t_user_data *player);
void			do_score_snake_size(int *score_snake_size_cooldown, t_user_data *player1, t_user_data *player2, t_score_anim **score_anims);
void			add_snake_score_anim(t_score_anim **score_anims, t_snake_part *head_snake, int score, t_color color_type);
void			print_score_anims(t_score_anim **score_anims, SDL_Renderer *renderer, TTF_Font *font);


#endif