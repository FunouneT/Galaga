#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:

	Enemy(sf::Texture&, sf::Vector2f);

	void update(sf::Vector2f, float);
};