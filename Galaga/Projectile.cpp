#include "Projectile.h"
#include "constants.h"
//#include <iostream>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f pos) : Entity(texture, pos)
{
	sprite.setScale(PROJECTILESPRITESCALE, PROJECTILESPRITESCALE);
}

void Projectile::update(float time)
{
	pos.y -= PROJECTILESPEED * time;
	sprite.setPosition(pos);
}