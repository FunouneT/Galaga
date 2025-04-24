#pragma once
#include <list>
#include "Player.h"

class Level1
{
public:
	
	Level1();

	void update(float);

	void draw(sf::RenderWindow&);

	int cooldown;

	Player* player;

	std::list<Entity*> projectiles;
};