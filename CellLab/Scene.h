#pragma once
#include "AdriansDefines.h"
#include "AdriansVector2s.h"
#include "AdriansInput.h"

#include "Editor.h"
#include "Petri.h"

class Scene {
public:
	Petri dish;
	sf::RenderWindow *window;

	bool petri = true;
	bool editor = false;

	float scrollradius = 30.f;
	float deltatime = 0.f;
	void start(sf::RenderWindow &w) {
		sf::Clock clock;
		sf::Event event;
		window = &w;
		while (window->isOpen()) {
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window->close();
				else if (event.type == sf::Event::MouseWheelMoved) { // Get scroll change
					scrollradius += (float)event.mouseWheel.delta * 2;
					if (scrollradius < 1.f)
						scrollradius = 1.f;
				}
			}
			deltatime = clock.restart().asSeconds();
			window->clear(sf::Color(250, 250, 255));
			//
			if (petri)
				Petridish();
			else if (editor)
				Editor();
			//
			window->display();

		}
	}

	void Editor() {

	}

	void Petridish() {
		dish.Call(*window, deltatime, scrollradius);
	}
};