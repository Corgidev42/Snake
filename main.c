#include <SDL2/SDL.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	SDL_version	compiled;
	SDL_version	linked;

	// Version de SDL utilisée à la compilation
	SDL_VERSION(&compiled);
	// Version de SDL utilisée à l'exécution
	SDL_GetVersion(&linked);
	printf("Version SDL compilée : %d.%d.%d\n", compiled.major, compiled.minor,
		compiled.patch);
	printf("Version SDL liée (runtime) : %d.%d.%d\n", linked.major,
		linked.minor, linked.patch);
	return (0);
}
