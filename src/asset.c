#include "snake.h"

int get_text_width(const char* text, TTF_Font* font)
{
	int width, height;

	if (TTF_SizeText(font, text, &width, &height) != 0)
		SDL_ExitWithError("Error while retrieving text width");
	return width;
}
int get_text_height(const char* text, TTF_Font* font)
{
	int width, height;

	if (TTF_SizeText(font, text, &width, &height) != 0)
		SDL_ExitWithError("Error while retrieving text height");
	return height;
}
void render_text(SDL_Renderer* renderer, const char* text, SDL_Rect rect, TTF_Font* font, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	if (!surface)
		SDL_ExitWithError("Failed to creation of surface");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		SDL_ExitWithError("Failed to creation of texture");
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}
