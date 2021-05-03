#pragma once
#include "Cell.h"

class FatCell : public Cell {
public:
	sf::CircleShape body;
	sf::CircleShape fat;

	float fatstored = 4.f;

	FatCell::FatCell() {
		//position = Vector2(400, 200);
		//radius = 50.f;


		body.setFillColor(sf::Color(c[0], c[1], c[2], 125));
		fat.setFillColor(sf::Color(163, 124, 75));
		body.setOutlineThickness(2.f);
		body.setOutlineColor(sf::Color(c[0] - 30, c[1] - 30, c[2] - 30));
		// End of setup

	}

	FatCell::FatCell(Vector2 mouseposition) {
		position = mouseposition;

		body.setFillColor(sf::Color(c[0], c[1], c[2], 125));
		fat.setFillColor(sf::Color(163, 124, 75));
		body.setOutlineThickness(2.f);
		body.setOutlineColor(sf::Color(c[0] - 30, c[1] - 30, c[2] - 30));
	}

	void Draw(sf::RenderWindow &window) {
		body.setPosition(position.asSF());
		body.setRadius(radius);
		body.setRotation(angle);

		fat.setPosition(position.asSF());
		fat.setRadius(fatstored);
		fat.setRotation(angle);

		body.setOrigin(radius, radius);
		fat.setOrigin(radius / 2, radius / 2);

		window.draw(fat);
		window.draw(body);
	}

	void Update(float deltatime, CellList &cells, Foodlist &fl) {
		Vector2 something = Cell::CheckCollisions(cells);
		position = position + (something * deltatime);
	}
};