#ifndef COLOR_H
#define COLOR_H

#define BACKGROUND Color(5, 5, 40)	// Couleur du fond
#define PLANT Color(0, 255, 0)		// Couleur des plantes
#define PREY Color(255, 255, 255)	// Couleur des proies
#define PREDATOR Color(255, 0, 0)	// Couleur des prédateurs



// Classe définissant une couleur

class Color
{

public :

	int red;	// Composante rouge
	int green;	// Composante verte
	int blue;	// Composante bleue

	Color();
	Color(const Color& color);
	Color(int red, int green, int blue);

	void operator=(const Color& color);
};

#endif