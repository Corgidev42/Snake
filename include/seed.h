#ifndef SEED_H
# define SEED_H

# include "snake_together.h"

/**
 * @brief Initialise le seed du jeu et charge les décimales de π.
 *
 * @param seed Pointeur vers la structure t_seed à initialiser.
 *
 * Cette fonction effectue les étapes suivantes :
 * - Ouvre le fichier contenant les décimales de π ("pi_10000.txt").
 * - Alloue dynamiquement la mémoire pour stocker les 10000 premières décimales.
 * - Remplit les attributs de la structure `t_seed` (couleurs de lumière,
	smooth, etc.).
 * - Calcule les pourcentages de génération d'arbres et de rochers.
 *
 * En cas d'erreur (fichier introuvable ou échec d'allocation),
	le programme quitte.
 */
void	init_seed(t_seed *seed);

/**
 * @brief Génère un hash basé sur le seed et les coordonnées.
 *
 * @param x Coordonnée X utilisée dans le calcul du hash.
 * @param y Coordonnée Y utilisée dans le calcul du hash.
 * @return int Valeur absolue du hash généré.
 *
 * Cette fonction génère un hash en combinant le seed du jeu (`App.seed.number`)
 * avec les coordonnées `(x,
	y)`. Elle utilise les décimales de π pour obtenir un
 * résultat pseudo-aléatoire stable entre 0 et 999.
 *

	* La fonction retourne un nombre à trois chiffres généré en extrayant trois chiffres
 * successifs des décimales de π.
 */
int		seed_hash(int x, int y);

#endif // SEED_H
