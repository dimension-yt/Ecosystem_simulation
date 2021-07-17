#include "display.h"
#include "prey.h"



// Met à jour l'état d'une proie

void update_prey(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int prey_time_no_eat_max, int prey_nb_eat_kid, int number_plants)
{
	world[x][y].done = true;

	if (world[x][y].time_no_eat >= prey_time_no_eat_max)
	{
		world[x][y] = Cell();
		show_cell(x, y, empty, zoom);
		return;
	}

	if (world[x][y].nb_eat >= prey_nb_eat_kid)
	{
		prey_make_kid(world, x, y, zoom, 1);
		world[x][y].nb_eat = 0;
		return;
	}

	if ((x > 0 and world[x - 1][y].type == plant) or (y > 0 and world[x][y - 1].type == plant) or (y < world.front().size() - 1 and world[x][y + 1].type == plant) or (x < world.size() - 1 and world[x + 1][y].type == plant))
	{
		world[x][y].time_no_eat = 0;
		world[x][y].nb_eat++;
		eat_plant(world, x, y, zoom);
	}

	else if (number_plants > 0)
	{
		world[x][y].time_no_eat++;
		move_prey(world, x, y, zoom, 1);
	}

	else
		world[x][y].time_no_eat++;
}



// Fais bouger une proie vers la plante la plus proche

int move_prey(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int off)
{
	Cell temp = Cell();
	int offset = off * (rand() % 2 == 0 ? -1 : 1);
	bool priority = rand() % 2;

	if ((x + 1 >= world.size() or !is_walkable(world[x + 1][y].type)) and (x - 1 < 0 or !is_walkable(world[x - 1][y].type)) and (y + 1 >= world.front().size() or !is_walkable(world[x][y + 1].type)) and (y - 1 < 0 or !is_walkable(world[x][y - 1].type)))
		return (-1);

	if (!priority)
	{
		for (int x_off = -off; x_off <= off; x_off++)
		{
			if (y - offset < world.front().size() and y - offset >= 0 and x + x_off >= 0 and x + x_off < world.size() and world[x + x_off][y - offset].type == plant and (world[x][y - sign(offset)].type == empty or world[x][y - sign(offset)].type == plant))
			{
				world[x][y - sign(offset)] = world[x][y];
				show_cell(x, y - sign(offset), prey, zoom);

				world[x][y] = temp;
				show_cell(x, y, world[x][y].type, zoom);

				return 1;
			}

			if (y + offset >= 0 and y + offset < world.front().size() and x + x_off >= 0 and x + x_off < world.size() and world[x + x_off][y + offset].type == plant and (world[x][y + sign(offset)].type == empty or world[x][y + sign(offset)].type == plant))
			{
				world[x][y + sign(offset)] = world[x][y];
				show_cell(x, y + sign(offset), prey, zoom);

				world[x][y] = temp;
				show_cell(x, y, world[x][y].type, zoom);

				return 1;
			}
		}

		offset = off * (rand() % 2 == 0 ? -1 : 1);
	}

	for (int y_off = -off; y_off <= off; y_off++)
	{
		if (x - offset < world.size() and x - offset >= 0 and y + y_off >= 0 and y + y_off < world.front().size() and world[x - offset][y + y_off].type == plant and (world[x - sign(offset)][y].type == empty or world[x - sign(offset)][y].type == plant))
		{
			world[x - sign(offset)][y] = world[x][y];
			show_cell(x - sign(offset), y, prey, zoom);

			world[x][y] = temp;
			show_cell(x, y, world[x][y].type, zoom);

			return 1;
		}

		if (x + offset >= 0 and x + offset < world.size() and y + y_off >= 0 and y + y_off < world.front().size() and world[x + offset][y + y_off].type == plant and (world[x + sign(offset)][y].type == empty or world[x + sign(offset)][y].type == plant))
		{
			world[x + sign(offset)][y] = world[x][y];
			show_cell(x + sign(offset), y, prey, zoom);

			world[x][y] = temp;
			show_cell(x, y, world[x][y].type, zoom);

			return 1;
		}
	}

	if (priority)
	{
		offset = off * (rand() % 2 == 0 ? -1 : 1);
		for (int x_off = -off; x_off <= off; x_off++)
		{
			if (y - offset < world.front().size() and y - offset >= 0 and x + x_off >= 0 and x + x_off < world.size() and world[x + x_off][y - offset].type == plant and (world[x][y - sign(offset)].type == empty or world[x][y - sign(offset)].type == plant))
			{
				world[x][y - sign(offset)] = world[x][y];
				show_cell(x, y - sign(offset), prey, zoom);

				world[x][y] = temp;
				show_cell(x, y, world[x][y].type, zoom);

				return 1;
			}

			if (y + offset >= 0 and y + offset < world.front().size() and x + x_off >= 0 and x + x_off < world.size() and world[x + x_off][y + offset].type == plant and (world[x][y + sign(offset)].type == empty or world[x][y + sign(offset)].type == plant))
			{
				world[x][y + sign(offset)] = world[x][y];
				show_cell(x, y + sign(offset), prey, zoom);

				world[x][y] = temp;
				show_cell(x, y, world[x][y].type, zoom);

				return 1;
			}
		}
	}

	if (x - off < 0 and x + off >= world.size() and y - off < 0 and y + off >= world.front().size())
		return -1;

	return move_prey(world, x, y, zoom, off + 1);
}



// Fais manger une plante à une proie

void eat_plant(std::vector<std::vector<Cell>>& world, int x, int y, int zoom)
{
	std::vector<int> order = random_order_4();

	for (int r = 0; r < 4; r++)
	{
		switch (order[r])
		{

		case 0:

			if (x > 0 and world[x - 1][y].type == plant)
			{
				world[x - 1][y] = Cell();
				show_cell(x - 1, y, empty, zoom);

				return;
			}

			break;

		case 1:

			if (y > 0 and world[x][y - 1].type == plant)
			{
				world[x][y - 1] = Cell();
				show_cell(x, y - 1, empty, zoom);

				return;
			}

			break;

		case 2:

			if (y < world.front().size() - 1 and world[x][y + 1].type == plant)
			{
				world[x][y + 1] = Cell();
				show_cell(x, y + 1, empty, zoom);

				return;
			}

			break;

		case 3:

			if (x < world.size() - 1 and world[x + 1][y].type == plant)
			{
				world[x + 1][y] = Cell();
				show_cell(x + 1, y, empty, zoom);

				return;
			}

			break;
		}
	}
}



// Crée une nouvelle proie à côté d'une autre

int prey_make_kid(std::vector<std::vector<Cell>>& world, int x, int y, int zoom, int off)
{
	int offset = off * (rand() % 2 == 0 ? -1 : 1);
	bool priority = rand() % 2;

	if (!priority)
	{
		for (int x_off = -off; x_off <= off; x_off++)
		{
			if (y - offset < world.front().size() and y - offset >= 0 and x + x_off >= 0 and x + x_off < world.size() and (world[x + x_off][y - offset].type == empty or world[x + x_off][y - offset].type == plant))
			{
				world[x + x_off][y - offset] = Cell(prey);
				return 1;
			}
			if (y + offset >= 0 and y + offset < world.front().size() and x + x_off >= 0 and x + x_off < world.size() and (world[x + x_off][y + offset].type == empty or world[x + x_off][y + offset].type == plant))
			{
				world[x + x_off][y + offset] = Cell(prey);
				return 1;
			}
		}

		offset = off * (rand() % 2 == 0 ? -1 : 1);
	}

	for (int y_off = -off; y_off <= off; y_off++)
	{
		if (x - offset < world.size() and x - offset >= 0 and y + y_off >= 0 and y + y_off < world.front().size() and (world[x - offset][y + y_off].type == empty or world[x - offset][y + y_off].type == plant))
		{
			world[x - offset][y + y_off] = Cell(prey);
			return 1;
		}

		if (x + offset >= 0 and x + offset < world.size() and y + y_off >= 0 and y + y_off < world.front().size() and (world[x + offset][y + y_off].type == empty or world[x + offset][y + y_off].type == plant))
		{
			world[x + offset][y + y_off] = Cell(prey);
			return 1;
		}
	}

	if (priority)
	{
		offset = off * (rand() % 2 == 0 ? -1 : 1);
		for (int x_off = -off; x_off <= off; x_off++)
		{
			if (y - offset < world.front().size() and y - offset >= 0 and x + x_off >= 0 and x + x_off < world.size() and (world[x + x_off][y - offset].type == empty or world[x + x_off][y - offset].type == plant))
			{
				world[x + x_off][y - offset] = Cell(prey);
				return 1;
			}

			if (y + offset >= 0 and y + offset < world.front().size() and x + x_off >= 0 and x + x_off < world.size() and (world[x + x_off][y + offset].type == empty or world[x + x_off][y + offset].type == plant))
			{
				world[x + x_off][y + offset] = Cell(prey);
				return 1;
			}
		}
	}

	if (x - off < 0 and x + off >= world.size() and y - off < 0 and y + off >= world.front().size())
		return -1;

	return prey_make_kid(world, x, y, zoom, off + 1);
}