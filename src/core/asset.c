#include "snake_together.h"

// Module Assets / Bonus

// Les fonctions qui gèrent la logique liée aux bonus

t_bonus	get_random_bonus(void)
{
	int	random = rand() % App.nb_bonus;

	if (App.available_bonus[random] == LIFE_UP)
	{
		if (rand() % 10 == 0)
			return LIFE_UP;
		return get_random_bonus();
	}
	return App.available_bonus[random];
}
