#pragma once
#include "AdriansVector2s.h"
#include "AdriansDefines.h"
#include "AdriansInput.h"

#define petriradius 480.f

#include "Food.h"
#include "Cell.h"
#include "FatCell.h"
#include "EmptyCell.h"


class Petri {
private:
	float deltatime = 0.f;
public:

	CellList cellVector;
	Foodlist foodVector;
	sf::CircleShape petri;

	sf::CircleShape mouse;
	bool drawmouse = false;

	Petri() {
		foodVector.resize(0);

		petri.setPointCount(128);
		petri.setRadius(petriradius);
		petri.setOutlineThickness(10.f);
		petri.setOutlineColor(sf::Color(150, 150, 200));
		petri.setFillColor(sf::Color(220, 220, 255));
		petri.setPosition(WINDOWX / 2, WINDOWY / 2);
		petri.setOrigin(petri.getRadius(), petri.getRadius());

		mouse.setRadius(50.f);
		mouse.setOrigin(mouse.getRadius(), mouse.getRadius());
		mouse.setFillColor(sf::Color(10, 10, 10, 90));
		mouse.setOutlineThickness(2.f);
		mouse.setOutlineColor(sf::Color(10, 10, 10, 200));
		mouse.setPointCount(64);
	}

	float mfoodspawnrate = 0.01f;
	float foodspawnrate = mfoodspawnrate;
	int maxfoodspawn = FOOD_MAX_SPAWN;

	newPressMouse leftclick = newPressMouse(sf::Mouse::Left);
	newPressKey resetkey = newPressKey(sf::Keyboard::R);

	//
	newPressKey placekeyEmptyCell = newPressKey(sf::Keyboard::E);
	newPressKey placekeyFatCell = newPressKey(sf::Keyboard::F);

	void Call(sf::RenderWindow &window, float dt, float scrollradius) {  // Basically the main update
		deltatime = dt;
		/*
		if (leftclick.isPressed()) {
			cellVector.push_back(new FatCell(asVector2(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))))));
		}*/
		if (resetkey.isPressed()) {
			for (Cell* p : cellVector)
				delete p;
			cellVector.clear();
			cellVector.resize(0);
		}

		if (placekeyFatCell.isPressed()) 
			cellVector.push_back(new FatCell(asVector2(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))))));
		if (placekeyEmptyCell.isPressed())
			cellVector.push_back(new EmptyCell(asVector2(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))))));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			cellVector.push_back(new EmptyCell(asVector2(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))))));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			foodVector.resize(foodVector.size() + 1);
			foodVector.back().position = asVector2(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
			foodVector.back().body.setPosition(foodVector.back().position.asSF());
			foodVector.back().food = 50.f;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			Vector2 pos = asVector2(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
			mouse.setPosition(pos.asSF());
			mouse.setRadius(scrollradius);
			mouse.setOrigin(scrollradius, scrollradius);
			Vector2 pushback = Vector2(0.f, 0.f);
			for (int i = 0; i < cellVector.size(); i++) {
				Cell *ptr = cellVector[i];
				float distance = pos.distanceTo(ptr->position);
				if (distance < mouse.getRadius() + ptr->radius + 4.f) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						pushback = (ptr->position - pos) * -1;
					else 
						pushback = (ptr->position - pos);
					pushback = pushback * (distance * 0.1f);
					ptr->position = ptr->position + (pushback * dt);
				}
			}
			drawmouse = true;
		}
		else {
			drawmouse = false;
		}

		Update(deltatime);
		Draw(window);
	}


	void Update(float deltatime) {
		if (foodspawnrate < 0.f) {
			if (foodVector.size() < maxfoodspawn)
				foodVector.resize(foodVector.size() + 1);
			foodspawnrate = mfoodspawnrate;
		}
		else {
			foodspawnrate -= 1 * deltatime;
		}

		for (int i = 0; i < foodVector.size(); i++) {
			foodVector[i].grow(deltatime);
		}

		for (int i = 0; i < cellVector.size(); i++) { // Update
			cellVector[i]->Update(deltatime, cellVector, foodVector);
		}

		for (int i = 0; i < cellVector.size(); i++) {
			if (cellVector[i]->die) {
				cellVector.erase(cellVector.begin() + i); // Possible memory leak when deleting pointer
				continue;
			}

			if (cellVector[i]->split) {
				cellVector[i]->split = false;

				cellVector.push_back(new EmptyCell(cellVector[i]->position + Vector2(getrandom(-1000, 1000) / 100, getrandom(-1000, 1000) / 100)));
				cellVector.back()->food = cellVector[i]->food / 3;
				cellVector.back()->c[0] = cellVector[i]->c[0];
				cellVector.back()->c[1] = cellVector[i]->c[1];
				cellVector.back()->c[2] = cellVector[i]->c[2];
				cellVector.back()->SetColor();
				cellVector[i]->food = cellVector[i]->food - cellVector[i]->food / 3;
				cellVector[i]->UpdateRadius();
				cellVector.back()->UpdateRadius();
			}
		}
	}

	void Draw(sf::RenderWindow &window) {
		window.draw(petri);

		for (int i = 0; i < foodVector.size(); i++) {
			window.draw(foodVector[i].body);
		}

		for (int i = 0; i < cellVector.size(); i++) {
			cellVector[i]->Draw(window);
		}

		if (drawmouse)
			window.draw(mouse);
	}
};