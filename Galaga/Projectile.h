#pragma once

#include "Entity.h"

class Projectile : public Entity
{
private:

public:

	Projectile(sf::Texture&, sf::Vector2f);

	void update(float);
};

