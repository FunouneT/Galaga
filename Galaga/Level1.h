#pragma once
#include <list>
#include "Player.h"

class Level1
{
public:
	
	Level1();

	void update(float);

	void draw(sf::RenderWindow&);
	
	int projectileCD;

	int enemySpawnCD;

	int countOfEnemies;

	Player* player;

	std::list<Entity*> projectiles;

	std::list<Entity*> enemies;
};