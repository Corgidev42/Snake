#include "snake.h"

void	print_scoreboard(SDL_Rect rect_pos, t_user_data player1, t_user_data player2)
{
	if(SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
		SDL_ExitWithError("print_scoreboard : color in white");

	if(SDL_RenderDrawRect(App.renderer, &rect_pos))
		SDL_ExitWithError("print_scoreboard : draw rect");

	rect_pos.y += SCOREBOARD_HEIGHT / 2 - get_text_height("A", App.font) / 2;
	SDL_Rect player_text_rect ={rect_pos.x + 20, rect_pos.y, get_text_width("Player", App.font), get_text_height("Player", App.font)};
	SDL_Rect score_text_rect = {rect_pos.x + 120 + get_text_width("A", App.font), rect_pos.y, get_text_width("score", App.font), get_text_height("score", App.font)};
	SDL_Rect life_text_rect ={rect_pos.x + 220 + get_text_width("A", App.font) + get_text_width("99999", App.font), rect_pos.y, get_text_width("life", App.font), get_text_height("life", App.font)};

	SDL_Rect id_rect_player1 = {player_text_rect.x + get_text_width("Player", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player1.id), App.font), get_text_height(ft_itoa(player1.id), App.font)};
	SDL_Rect score_rect_player1 = {score_text_rect.x + get_text_width("score", App.font) + 5, rect_pos.y,  get_text_width(ft_itoa(player1.score), App.font), get_text_height(ft_itoa(player1.score), App.font)};
	SDL_Rect life_rect_player1 = {life_text_rect.x + get_text_width("life", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player1.life), App.font), get_text_height(ft_itoa(player1.life), App.font)};


	render_text(App.renderer, "Player", player_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "score", score_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "life", life_text_rect, App.font, (SDL_Color){255, 255, 255, 255});

	render_text(App.renderer, ft_itoa(player1.id), id_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player1.score), score_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player1.life), life_rect_player1, App.font, (SDL_Color){255, 255, 255, 255});

	player_text_rect.x = SCREEN_WIDTH - 20 - get_text_width("Player", App.font) - get_text_width("A", App.font);
	score_text_rect.x = SCREEN_WIDTH - 120 - get_text_width("score", App.font) - get_text_width("99999", App.font);
	life_text_rect.x = SCREEN_WIDTH - 220  - get_text_width("life", App.font) - get_text_width("A", App.font) - get_text_width("99999", App.font);

	SDL_Rect id_rect_player2 = {player_text_rect.x + get_text_width("Player", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player2.id), App.font), get_text_height(ft_itoa(player2.id), App.font)};
	SDL_Rect score_rect_player2 = {score_text_rect.x + get_text_width("score", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player2.score), App.font), get_text_height(ft_itoa(player2.score), App.font)};
	SDL_Rect life_rect_player2 = {life_text_rect.x + get_text_width("life", App.font) + 5, rect_pos.y, get_text_width(ft_itoa(player2.life), App.font), get_text_height(ft_itoa(player2.life), App.font)};

	render_text(App.renderer, "Player", player_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "score", score_text_rect, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, "life", life_text_rect, App.font, (SDL_Color){255, 255, 255, 255});

	render_text(App.renderer, ft_itoa(player2.id), id_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player2.score), score_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
	render_text(App.renderer, ft_itoa(player2.life), life_rect_player2, App.font, (SDL_Color){255, 255, 255, 255});
}