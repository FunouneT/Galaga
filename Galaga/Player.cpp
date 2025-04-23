#include "Player.h"
//#include "Projectile.h"
#include "constants.h"

Player::Player(sf::Texture& texture, sf::Vector2f pos) : Entity(texture, pos)
{
	sprite.setScale(PLAYERSPRITESCALE, PLAYERSPRITESCALE);
	//sprite.setOrigin(sf::Vector2f(texture.getSize().x / 10, texture.getSize().y / 10));
}

//void Player::shoot()
//{
//	Projectile* projectile()
//}

void Player::update(float posX, float time)
{
	pos.x += posX * time;
	sprite.setPosition(pos);
}