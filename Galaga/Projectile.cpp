#include "Projectile.h"
#include "constants.h"
//#include <iostream>

Projectile::Projectile(sf::Texture& texture, sf::Vector2f pos) : Entity(texture, pos)
{
	sprite.setScale(PROJECTILESPRITESCALE, PROJECTILESPRITESCALE);
	//sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	//std::cout << "Projectile created" << std::endl;
}

void Projectile::update(float time)
{
	pos.y -= PROJECTILESPEED * time;
	sprite.setPosition(pos);
}