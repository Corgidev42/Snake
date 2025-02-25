#ifndef ASSET_H
# define ASSET_H

# include "snake.h"

int			get_text_width(const char *text, TTF_Font *font);
int			get_text_height(const char *text, TTF_Font *font);
void		render_text(SDL_Renderer *renderer, const char *text, SDL_Rect rect,
				TTF_Font *font, SDL_Color color);
SDL_Texture	*load_texture(const char *path);

#endif
