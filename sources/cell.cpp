#include "cell.h"
#include "display.h"



// Crée une case

Cell::Cell()
{
	type = empty;
	done = false;
	nb_eat = 0;
	time_no_eat = 0;
}



// Crée une case à partir d'une autre case

Cell::Cell(const Cell& cell)
{
	type = cell.type;
	done = cell.done;
	nb_eat = cell.nb_eat;
	time_no_eat = cell.time_no_eat;
}



// Crée une case à partir d'un type donné

Cell::Cell(Type type)
{
	this->type = type;
	done = false;
	nb_eat = 0;
	time_no_eat = 0;
}



// Assignation

void Cell::operator=(const Cell& cell)
{
	type = cell.type;
	done = cell.done;
	nb_eat = cell.nb_eat;
	time_no_eat = cell.time_no_eat;
}



// Initialise le monde

void initialize_world(std::vector<std::vector<Cell>>& world, int world_width, int world_height, int nb_plants, int nb_preys, int nb_predators, int zoom)
{
	world.clear();
	std::vector<Cell> temp;

	int x = rand() % world_height;
	int y = rand() % world_width;

	for (int i = 0; i < world_width; i++)
		temp.push_back(Cell());

	for (int i = 0; i < world_height; i++)
		world.push_back(temp);

	for (int i = 0; i < nb_plants; i++)
	{
		while (world[x][y].type != empty)
		{
			x = rand() % world_height;
			y = rand() % world_width;
		}

		world[x][y] = Cell(plant);
		show_cell(x, y, plant, zoom);
	}

	for (int i = 0; i < nb_preys; i++)
	{
		while (world[x][y].type != empty)
		{
			x = rand() % world_height;
			y = rand() % world_width;
		}

		world[x][y] = Cell(prey);
		show_cell(x, y, plant, zoom);
	}

	for (int i = 0; i < nb_predators; i++)
	{
		while (world[x][y].type != empty)
		{
			x = rand() % world_height;
			y = rand() % world_width;
		}

		world[x][y] = Cell(predator);
		show_cell(x, y, plant, zoom);
	}
}



// Rajoute des cases de type plante autour des plantes déjà existantes

void grow_plant(std::vector<std::vector<Cell>>& world, int x, int y, int growth_rate, int zoom)
{
	Cell cell = Cell(plant);
	cell.done = true;

	if (x > 0 and world[x - 1][y].type == plant and !world[x - 1][y].done)
	{
		if (rand() % 100 < growth_rate)
		{
			world[x][y] = cell;
			show_cell(x, y, plant, zoom);
		}
	}

	if (y > 0 and world[x][y - 1].type == plant and !world[x][y - 1].done)
	{
		if (rand() % 100 < growth_rate)
		{
			world[x][y] = cell;
			show_cell(x, y, plant, zoom);
		}
	}

	if (y < world.front().size() - 1 and world[x][y + 1].type == plant and !world[x][y + 1].done)
	{
		if (rand() % 100 < growth_rate)
		{
			world[x][y] = cell;
			show_cell(x, y, plant, zoom);
		}
	}

	if (x < world.size() - 1 and world[x + 1][y].type == plant and !world[x + 1][y].done)
	{
		if (rand() % 100 < growth_rate)
		{
			world[x][y] = cell;
			show_cell(x, y, plant, zoom);
		}
	}
}



// Enlève la sécurité qui empèche de prendre en compte plusieurs fois le même être vivant

void update_world(std::vector<std::vector<Cell>>& world)
{
	for (int i = 0; i < world.size(); i++)
	{
		for (int j = 0; j < world[0].size(); j++)
		{
			if (world[i][j].done == true)
				world[i][j].done = false;
		}
	}
}



// Donne 1 si la valeur est positive et -1 si la valeur est négative

int sign(int value)
{
	if (value >= 0)
		return 1;

	else
		return -1;
}



// Indique si on peut se déplacer sur cette case

int is_walkable(Type type)
{
	return (type == empty or type == plant);
}



// Donne un ordre aléatoire de 4 valeurs

std::vector<int> random_order_4()
{
	std::vector<int> vect;
	int random = rand() % 24;

	switch (random)
	{
		case 0:  vect = { 0, 1, 2, 3 }; break;
		case 1:  vect = { 0, 1, 3, 2 }; break;
		case 2:  vect = { 0, 2, 1, 3 }; break;
		case 3:  vect = { 0, 2, 3, 1 }; break;
		case 4:  vect = { 0, 3, 1, 2 }; break;
		case 5:  vect = { 0, 3, 2, 1 }; break;
		case 6:  vect = { 1, 0, 2, 3 }; break;
		case 7:  vect = { 1, 0, 3, 2 }; break;
		case 8:  vect = { 1, 2, 0, 3 }; break;
		case 9:  vect = { 1, 2, 3, 0 }; break;
		case 10: vect = { 1, 3, 0, 2 }; break;
		case 11: vect = { 1, 3, 2, 0 }; break;
		case 12: vect = { 2, 0, 1, 3 }; break;
		case 13: vect = { 2, 0, 3, 1 }; break;
		case 14: vect = { 2, 1, 0, 3 }; break;
		case 15: vect = { 2, 1, 3, 0 }; break;
		case 16: vect = { 2, 3, 0, 1 }; break;
		case 17: vect = { 2, 3, 1, 0 }; break;
		case 18: vect = { 3, 0, 1, 3 }; break;
		case 19: vect = { 3, 0, 2, 1 }; break;
		case 20: vect = { 3, 1, 0, 2 }; break;
		case 21: vect = { 3, 1, 2, 0 }; break;
		case 22: vect = { 3, 2, 0, 1 }; break;
		case 23: vect = { 3, 2, 1, 0 }; break;
	}

	return vect;
}