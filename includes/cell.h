#ifndef CELL_H
#define CELL_H
#include "color.h"
#include <vector>
#include <random>



// Type d'�tre vivant

enum Type { empty, plant, prey, predator };



// Classe d�finissant une case du monde

class Cell
{

public:

	Type type;			// Type d'�tre vivant
	bool done;			// S�curit� emp�chant de mettre � jour deux fois le m�me �tre vivant
	int nb_eat;			// Nombre de fois o� l'animal a mang�
	int time_no_eat;	// Temps pass� sans manger

	Cell();
	Cell(const Cell& cell);
	Cell(Type type);

	void operator=(const Cell& cell);
};

void initialize_world(std::vector<std::vector<Cell>>& world, int world_width, int world_height, int nb_plants, int nb_preys, int nb_predators, int zoom);
void grow_plant(std::vector<std::vector<Cell>>& world, int x, int y, int growth_rate, int zoom);
void update_world(std::vector<std::vector<Cell>>& world);
int sign(int value);
int is_walkable(Type type);
std::vector<int> random_order_4();

#endif