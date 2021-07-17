#include "color.h"



// Cr�e une couleur

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}



// Cr�e une couleur � partir d'une autre

Color::Color(const Color& color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
}



// Cr�e une couleur � partir de ses composantes rouges, vertes et bleues

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