#pragma once
#include "Cell.h"

class EmptyCell : public Cell {
public:
	sf::CircleShape body;

	EmptyCell() {
		body.setFillColor(sf::Color(c[0], c[1], c[2], 125));
		body.setOutlineThickness(2.f);
		body.setOutlineColor(sf::Color(c[0] - 30, c[1] - 30, c[2] - 30));
	}

	EmptyCell::EmptyCell(Vector2 mouseposition) {
		position = mouseposition;

		body.setFillColor(sf::Color(c[0], c[1], c[2], 125));
		body.setOutlineThickness(2.f);
		body.setOutlineColor(sf::Color(c[0] - 30, c[1] - 30, c[2] - 30));
	}
	void SetColor() {
		body.setFillColor(sf::Color(c[0], c[1], c[2], 125));
		body.setOutlineColor(sf::Color(c[0] - 30, c[1] - 30, c[2] - 30));
	}

	void Draw(sf::RenderWindow &window) {
		body.setPosition(position.asSF());
		body.setRadius(food);
		body.setRotation(angle);
		body.setOrigin(food, food);

		window.draw(body);
	}

	void Jiggle(float dt) {
		float rads = asRadians(getrandom(1, 360));
		Vector2 direction = Vector2(cos(rads), sin(rads));
		direction = direction * 500;
		if ((position + (direction *dt)).distanceTo(Vector2(WINDOWX/2,WINDOWY/2)) < petriradius - radius - 2.f)
			position = position + (direction * dt);
	}

	void Update(float deltatime, CellList &cells, Foodlist &foodlist) {
		Jiggle(deltatime);
		Age(deltatime);
		for (int i = 0; i < foodlist.size(); i++) {
			if (position.distanceTo(asVector2(foodlist[i].body.getPosition())) < radius) {
				food = food + foodlist[i].food / 9;
				radius = food;
				foodlist.erase(foodlist.begin() + i);
			}
		}
		if (food > 15.f)
			split = true;
		Vector2 something = Cell::CheckCollisions(cells);
		radius = food;
		if ((position + (something * deltatime)).distanceTo(Vector2(WINDOWX/2, WINDOWY/2)) < petriradius - radius - 2.f)
			position = position + (something * deltatime);
	}
};