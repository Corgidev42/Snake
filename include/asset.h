#ifndef ASSETS_H
# define ASSETS_H

# include "snake_together.h"

/**
 * @brief Sélectionne un bonus aléatoire parmi ceux disponibles.
 *
 * @return t_bonus Le bonus sélectionné aléatoirement.
 *
 * Cette fonction effectue les étapes suivantes :
 * - Sélectionne un bonus aléatoirement dans `App.available_bonus`.
 * - Applique une rareté spéciale pour le bonus `LIFE_UP` (1 chance sur 10).
 * - Si `LIFE_UP` est sélectionné mais ne respecte pas la probabilité,
 *   la fonction est rappelée récursivement pour en choisir un autre.
 *
 * Le bonus retourné est un des éléments suivants :
 * - `LIFE_UP`
 * - `TP`
 * - `STAR`
 * - `SLOW`
 */
t_bonus	get_random_bonus(void);

#endif // ASSETS_H
