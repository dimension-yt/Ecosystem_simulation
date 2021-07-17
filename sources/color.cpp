#include "color.h"



// Crée une couleur

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}



// Crée une couleur à partir d'une autre

Color::Color(const Color& color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
}



// Crée une couleur à partir de ses composantes rouges, vertes et bleues

Color::Color(int red, int green, int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}



// Assignation

void Color::operator=(const Color& color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
}