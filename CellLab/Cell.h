#pragma once
#include "AdriansDefines.h"
#include "AdriansInput.h"
#include "AdriansVector2s.h"
#include <SFML/Graphics.hpp>

#include "Food.h"
#include "Joint.h"

class Cell;
typedef std::vector<Cell *> CellList;
class Cell {
public:
	Vector2 position = Vector2(0.f, 0.f);
	Vector2 velocity = Vector2(0.f, 0.f);
	float angle = 0;

	float food = 6.f;
	float radius = food;

	//int c[3] = {getrandom(90, 255), getrandom(90, 255), getrandom(90, 255)};
	int c[3] = { getrandom(35, 36), getrandom(90, 255), getrandom(35, 36) };

	bool touched = false;
	bool split = false;
	bool die = false;
	float splitangle = 90.f;

	std::vector<Joint> joints;
	Cell() {
		joints.resize(0);
	}

	void UpdateRadius() {
		radius = food;
	}

	virtual void SetColor() {}
	virtual void Update(float deltatime, CellList &cl, Foodlist &fl) {}
	virtual void Draw(sf::RenderWindow &window) {}

	void Age(float deltatime) {
		radius = food;
		food = food - (0.25f * deltatime);
		if (food < 0.1f) // 0.25f;
			die = true;
	}

	Vector2 CheckCollisions(CellList &cellvectorptr) {
		Vector2 pushback = Vector2(0.f, 0.f);
		Vector2 totalback = Vector2(0.f, 0.f);
		int total = 0;
		for (int i = 0; i < cellvectorptr.size(); i++) {
			Cell *ptr = cellvectorptr[i];
			if (ptr == this) {
				continue;
			}
			float distance = position.distanceTo(ptr->position);
			if (distance < radius + ptr->radius + 4.f) {
				pushback = (ptr->position - position) * -1;
				pushback = pushback * (distance * 0.2) * CELL_PUSHBACK;
				totalback = totalback + pushback;
				total++;
				touched = true;
			}
			else {
				touched = false;
			}
		}
		if (total > 0)
			return totalback / total;
		else {
			return pushback;
		}
	}
};