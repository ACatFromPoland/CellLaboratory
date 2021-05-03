#pragma once
#include "AdriansVector2s.h"
#include "AdriansDefines.h"
#include "AdriansInput.h"

class Food;
typedef std::vector<Food> Foodlist;
class Food {
public:
	sf::CircleShape body;
	float food = FOOD_START_FOOD;
	float radius = FOOD_STARD_RADIUS;
	float growthrate = FOOD_GROWTH_RATE;
	float maxsize = FOOD_MAX_SIZE;
	Vector2 position = Vector2(0.f, 0.f);
	Food() {
		body.setPointCount(32);
		body.setRadius(radius);
		body.setFillColor(sf::Color::Green);
		Generate();
	}

	void Generate() {
		float radius = petriradius;
		float angle = (float)getrandom(0, 360);
		float rads = (float)asRadians(angle);
		Vector2 direction = Vector2(cos(rads), sin(rads));
		direction = direction * getrandom(10.f, radius - (FOOD_MAX_SIZE * 2));
		direction = direction + Vector2(450.f * 2 - 3.f, 498.f);
		body.setPosition(direction.asSF());
	}

	void grow(float deltatime) {
		if (radius < maxsize) {
			radius += growthrate * deltatime;
			food = radius * 2.5f;
			body.setRadius(radius);
			body.setOrigin(radius, radius);
		}
	}
};