#include "snake.h"

// Fonction de transition avec compte à rebours
void countdown_transition(t_grid grid, t_user_data player1, t_user_data player2, t_gametick *gametick, SDL_Rect actions_rect_pos, SDL_Rect scoreboard_rect_pos)
{
	// Définir la durée du compte à rebours (en millisecondes)
	const Uint32	countdown_duration = gametick->timer;
	Uint32			start_time = SDL_GetTicks();
	Uint32			current_time;
	int				seconds_left;
	char			*countdown_text;
	SDL_Rect		text_rect;
	int				text_w;
	int				text_h;

	while (App.running && ((current_time = SDL_GetTicks()) - start_time < countdown_duration))
	{
		// Effacer l'écran en noir
		SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255);
		SDL_RenderClear(App.renderer);

		SDL_Event event;

		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				App.running = SDL_FALSE;

		print_grid(grid);
		print_snake(grid, player1.head_snake, gametick->snakes_animation);
		print_snake(grid, player2.head_snake, gametick->snakes_animation);
		print_obstacles(grid);
		print_is_pending(grid, gametick->object_cooldown);
		print_actions(actions_rect_pos, player1, player2);
		print_scoreboard(scoreboard_rect_pos, player1, player2);

		// Calcul du nombre de secondes restantes
		seconds_left = (countdown_duration - (current_time - start_time)) / 1000;
		if (seconds_left > 0)
			countdown_text = ft_itoa(seconds_left);
		else
			countdown_text = ft_strdup("Go!");

		// Calculer la taille du texte pour le centrer
		text_w = get_text_width(countdown_text, App.font) * 2;
		text_h = get_text_height(countdown_text, App.font) * 2;
		text_rect.x = SCREEN_WIDTH / 2 - text_w / 2;
		text_rect.y = SCREEN_HEIGHT / 2 - text_h / 2;
		text_rect.w = text_w;
		text_rect.h = text_h;

		// Afficher le texte du compte à rebours
		render_text(App.renderer, countdown_text, text_rect, App.font, (SDL_Color){255, 255, 255, 255});
		free(countdown_text);
		SDL_RenderPresent(App.renderer);
		SDL_Delay(1000 / 60);
	}
	// mettre à jour le temps écoulé
	gametick->elapsed_time = SDL_GetTicks();
}

void	game_window(t_user_data player1, t_user_data player2)
{
	t_grid		grid;
	t_gametick	gametick;
	SDL_Rect scoreboard_rect_pos = {SCOREBOARD_POS_X, SCOREBOARD_POS_Y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT};
	SDL_Rect actions_rect_pos = {ACTIONS_POS_X, ACTIONS_POS_Y, ACTIONS_WIDTH, ACTIONS_HEIGHT};
	SDL_Rect grid_rect_pos = {GRID_POS_X, GRID_POS_Y, GRID_WIDTH, GRID_HEIGHT};

	init_map(&grid);
	spawn_snake(&grid, &player1);
	spawn_snake(&grid, &player2);
	init_gametick(&gametick);

	countdown_transition(grid, player1, player2, &gametick, actions_rect_pos, scoreboard_rect_pos);
	while (App.running && player1.life && player2.life)
	{
		update_gametick(&gametick, &player1, &player2);
		if(SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255))
			SDL_ExitWithError("Color set in black");
		if(SDL_RenderClear(App.renderer))
			SDL_ExitWithError("Render clear");

		do_input(&player1, &player2);

		died_animation(&grid, &gametick.snake_1_died_cooldown, &player1);
		died_animation(&grid, &gametick.snake_2_died_cooldown, &player2);

		move_snake(&grid, &gametick.snake_1_cooldown, &player1);
		move_snake(&grid, &gametick.snake_2_cooldown, &player2);

		do_actions(&player1, &player2, &gametick);

		do_collision(&grid, &player1, &player2);
		if (!player1.life || !player2.life)
			break;

		generate_apple(&grid, &gametick.apple_cooldown);
		generate_object(&grid,&gametick.object_cooldown);

		print_grid(grid);
		print_snake(grid, player1.head_snake, gametick.snakes_animation);
		print_snake(grid, player2.head_snake, gametick.snakes_animation);
		print_obstacles(grid);
		print_is_pending(grid, gametick.object_cooldown);
		print_actions(actions_rect_pos, player1, player2);
		print_scoreboard(scoreboard_rect_pos, player1, player2);

		SDL_RenderPresent(App.renderer);

		SDL_Delay(1000 / 60);
	}
	if (App.running)
		end_game_window(&player1, &player2);
}
