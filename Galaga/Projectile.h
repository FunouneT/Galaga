#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity
{
private:

	//float damage;

public:

	Projectile(sf::Texture&, sf::Vector2f);

	void update(float);
};

