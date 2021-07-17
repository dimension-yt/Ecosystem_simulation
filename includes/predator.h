#ifndef PREDATOR_H
#define PREDATOR_H

#include "cell.h"

# ifndef sign(value)
# define sign(value) (value >= 0 ? 1 : -1)
#endif

void update_predator(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int predator_time_no_eat_max, int predator_nb_eat_kid, int number_preys);
int move_predator(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int offset);
void eat_prey(std::vector<std::vector<Cell>>& world, int x, int y, int zoom);
int predator_make_kid(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int off);

#endif