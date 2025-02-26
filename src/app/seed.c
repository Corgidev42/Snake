#include "snake_together.h"

// Ce module gère la génération du « seed » ainsi que les fonctions associées (par exemple le hachage basé sur les décimales de π).

void	init_seed(t_seed *seed)
{
	int	tmp_seed;
	int	fd;

	tmp_seed = seed->number;
	fd = open("pi_10000.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open pi_10000.txt\n");
		exit(EXIT_FAILURE);
	}
	seed->pi_decimals = malloc(sizeof(char) * 10001);
	if (!seed->pi_decimals)
	{
		printf("Failed to malloc pi_decimals\n");
		exit(EXIT_FAILURE);
	}
	read(fd, seed->pi_decimals, 10000);
	seed->pi_decimals[10000] = '\0';
	close(fd);
	seed->is_yellow_light = (tmp_seed & 1);
	tmp_seed >>= 1;
	seed->is_green_light = (tmp_seed & 1);
	tmp_seed >>= 1;
	seed->is_blue_light = (tmp_seed & 1);
	tmp_seed >>= 1;
	seed->smooth = (tmp_seed & 1);
	tmp_seed >>= 1;
	seed->tree_percent = 30 + ((tmp_seed & 0b111111) % 40);
	seed->rock_percent = 100 - seed->tree_percent;
	tmp_seed >>= 6;
}

int	seed_hash(int x, int y)
{
	int	seed_number;
	int	hash;
	int	result;

	seed_number = App.seed.number;
	result = 0;
	hash = (seed_number * x + seed_number * y) % 10000;
	printf("hash = %d\n", hash);
	result += App.seed.pi_decimals[hash] - '0';
	result *= 10;
	result += App.seed.pi_decimals[hash + 1] - '0';
	result *= 10;
	result += App.seed.pi_decimals[hash + 2] - '0';
	return (abs(result));
}
