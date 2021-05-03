Step 1 -
Properties-
Config = All configs

In C++ }   Additional Include Dicts "c:\SFMLVS\include"

In Linker } Additional Library Dicts "c:\SFMLVS\lib"
	Linker Input} Additional Dependencies  ";sfml-window.lib;sfml-system.lib;sfml-graphics.lib;sfml-audio.lib;sfml-network.lib;"

Select Debug Config
	Linker Input} "sfml-window-d.lib;sfml-system-d.lib;sfml-graphics-d.lib;sfml-audio-d.lib;sfml-network-d.lib;"


Step 2 -
	Get SFMLVS Bin .dlls'
	Place into solution with main.cpp File


Step 3 -
	Example Test Code


#include <SFML/Graphics.hpp>

#define WINDOWX 800
#define WINDOWY 800

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "Example Project", sf::Style::Close);


	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black); 
		//
		//
		//	
		//
		window.display(); 

	}
	return 0;
}