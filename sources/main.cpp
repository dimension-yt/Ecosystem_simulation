#include "cell.h"
#include "color.h"
#include "display.h"
#include "prey.h"
#include "predator.h"
#include "SDL.h"
#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* argv[])
{


	// ------------------------- Paramètres de la simulation -------------------------



	int	world_width = 320;				// Largeur du monde (en cases)
	int	world_height = 180;				// Hateur du monde (en cases)
	int	zoom = 6;						// Taille des cases (en pixels)

	int	nb_plants = 160;				// Nombre de plantes au début
	int	growth_rate = 15;				// Vitesse de l'évolution des plantes (en pourcents)

	int	nb_preys = 160;					// Nombre de proies au début
	int prey_time_no_eat_max = 30;		// Temps que tient une proie sans manger
	int prey_nb_eat_kid = 15;			// Nombre de plantes qu'une proie doit manger pour faire un enfant

	int	nb_predators = 20;				// Nombre de prédators au début
	int predator_time_no_eat_max = 60;	// Temps que tient un prédateur sans manger
	int predator_nb_eat_kid = 25;		// Nombre de proies qu'un prédateur doit manger pour faire un enfant

	int frame_rate_max = 144;			// FPS maximum (en images par seconde)



	// -------------------------------------------------------------------------------



	if (world_width < 1) world_width = 1;
	if (world_height < 1) world_height = 1;
	if (zoom < 1) zoom = 1;
	if (nb_plants < 0) nb_plants = 0;
	if (growth_rate < 0) growth_rate = 0;
	if (growth_rate > 100) growth_rate = 100;
	if (nb_preys < 0) nb_preys = 0;
	if (prey_time_no_eat_max < 1) prey_time_no_eat_max = 1;
	if (prey_nb_eat_kid < 1) prey_nb_eat_kid = 1;
	if (nb_predators < 0) nb_predators = 0;
	if (predator_time_no_eat_max < 1) predator_time_no_eat_max = 1;
	if (predator_nb_eat_kid < 1) predator_nb_eat_kid = 1;
	if (frame_rate_max < 1) frame_rate_max = 1;

	std::ofstream file_;
	file_.open("data.txt");

	int window_width = world_width * zoom;
	int window_height = world_height * zoom;

	std::vector<std::vector<Cell>> world;
	int number_plants = 0;
	int number_preys = 0;
	int number_predators = 0;

	SDL_Init(SDL_INIT_VIDEO);

	window = NULL;
	renderer = NULL;

	SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowTitle(window, "Ecosystem simulation");
	SDL_Event event;

	SDL_SetRenderDrawColor(renderer, BACKGROUND.red, BACKGROUND.green, BACKGROUND.blue, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	initialize_world(world, world_width, world_height, nb_plants, nb_preys, nb_predators, zoom);

	bool stop = true;

	while (1)
	{
		clock_t start = clock();

		number_plants = 0;
		number_preys = 0;
		number_predators = 0;

		for (int i = 0; i < world.size(); i++) // Boucle pour compter chaques types d'êtres vivants
		{
			for (int j = 0; j < world[0].size(); j++)
			{
				if (world[i][j].type == plant)
					number_plants++;

				if (world[i][j].type == prey)
					number_preys++;

				if (world[i][j].type == predator)
					number_predators++;
			}
		}

		if (stop)
		{
			for (int i = 0; i < world.size(); i++) // Boucle pour compter chaques types d'êtres vivants
			{
				for (int j = 0; j < world[0].size(); j++)
				{
					if (world[i][j].type == plant)
						show_cell(i, j, plant, zoom);

					if (world[i][j].type == prey)
						show_cell(i, j, prey, zoom);

					if (world[i][j].type == predator)
						show_cell(i, j, predator, zoom);
				}
			}

			SDL_RenderPresent(renderer);

			Sleep(1000);
			stop = false;
		}

		if (file_.is_open())
			file_ << number_plants << ", " << number_preys << ", " << number_predators << "\n"; // Remplie de fichier data.txt

		for (int i = 0; i < world.size(); i++) // Boucle du pas de temps de la simulation
		{
			for (int j = 0; j < world[0].size(); j++)
			{
				if (world[i][j].type == empty)
					grow_plant(world, i, j, growth_rate, zoom);

				if (world[i][j].type == prey and !world[i][j].done)
					update_prey(world, i, j, zoom, prey_time_no_eat_max, prey_nb_eat_kid, number_plants);

				if (world[i][j].type == predator and !world[i][j].done)
					update_predator(world, i, j, zoom, predator_time_no_eat_max, predator_nb_eat_kid, number_preys);
			}
		}

		update_world(world);

		SDL_RenderPresent(renderer);

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
		{
			file_.close();
			SDL_Quit();
			exit(1);
		}

		if (clock() - start < (1. / (double)frame_rate_max) * 1000.)
			Sleep(((1. / (double)frame_rate_max) * 1000.) - (clock() - start));
	}

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	file_.close();
	SDL_Quit();
	return 0;
}