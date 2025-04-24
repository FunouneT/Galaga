#include "Player.h"
#include "constants.h"

Player::Player(sf::Texture& texture, sf::Vector2f pos) : Entity(texture, pos)
{
	sprite.setScale(PLAYERSPRITESCALE, PLAYERSPRITESCALE);
}

void Player::update(float posX, float time)
{
	pos.x += posX * time;
	sprite.setPosition(pos);
}