#pragma once
#include "Entity.h"

class Player : public Entity
{
public:

	Player(sf::Texture&, sf::Vector2f);

	void update(float,float);

};

