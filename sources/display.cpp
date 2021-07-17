#include "display.h"
#include "SDL.h"



// Affiche un rectangle aux coordonnées voulues

void show_cell(int x, int y, const Type type, int zoom)
{
	if (type == plant)
		SDL_SetRenderDrawColor(renderer, PLANT.red, PLANT.green, PLANT.blue, SDL_ALPHA_OPAQUE);

	else if (type == prey)
		SDL_SetRenderDrawColor(renderer, PREY.red, PREY.green, PREY.blue, SDL_ALPHA_OPAQUE);

	else if (type == predator)
		SDL_SetRenderDrawColor(renderer, PREDATOR.red, PREDATOR.green, PREDATOR.blue, SDL_ALPHA_OPAQUE);

	else
		SDL_SetRenderDrawColor(renderer, BACKGROUND.red, BACKGROUND.green, BACKGROUND.blue, SDL_ALPHA_OPAQUE);

	SDL_Rect rectangle[1];

	rectangle[0].h = zoom;
	rectangle[0].w = zoom;
	rectangle[0].x = y * zoom;
	rectangle[0].y = x * zoom;

	SDL_RenderFillRect(renderer, rectangle);
}