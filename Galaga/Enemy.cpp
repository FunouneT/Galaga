#include "Enemy.h"
#include "constants.h"

Enemy::Enemy(sf::Texture& texture, sf::Vector2f pos) : Entity(texture, pos)
{
	sprite.setScale(ENEMYSPRITESCALE, ENEMYSPRITESCALE);
	//direction = Direction::Left;
}

void Enemy::update(sf::Vector2f newPos, float time)
{
	pos.x += newPos.x * time;
	pos.y += newPos.y * time;
	sprite.setPosition(pos);
}