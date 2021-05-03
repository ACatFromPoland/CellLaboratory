#include <SFML/Graphics.hpp>
#include "Scene.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "Cell Lab", sf::Style::Close);

	Scene scene;
	scene.start(window);

	return 0;
}

//************** To do and to fix *****************
// Fix Fat Cells
//
// Make Joint class to stick cells together
// Joint cells should share a food level
// Maybe a new organism class to handle joint cells??
// Make the cell editor!?!