#ifndef PREY_H
#define PREY_H
#include "cell.h"


void update_prey(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int prey_time_no_eat_max, int prey_nb_eat_kid, int number_plants);
int move_prey(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int offset);
void eat_plant(std::vector<std::vector<Cell>>& world, int x, int y, int zoom);
int prey_make_kid(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int off);

#endif