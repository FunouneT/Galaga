#include "Projectile.h"
#include "constants.h"

Projectile::Projectile(sf::Texture& texture, sf::Vector2f pos) : Entity(texture, pos)
{
    sprite.setScale(PROJECTILESPRITESCALE, PROJECTILESPRITESCALE);

    float playerCenterX = pos.x + PLAYERWIDTH * PLAYERSPRITESCALE / 2;
    this->pos.x = playerCenterX+24;
    this->pos.y = pos.y-40;
    sprite.setPosition(this->pos);
}
void Projectile::update(float time)
{
	pos.y -= PROJECTILESPEED * time;
	sprite.setPosition(pos);
}