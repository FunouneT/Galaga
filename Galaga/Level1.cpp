#include <SFML/Graphics.hpp>
#include "Level1.h"
#include "Player.h"
#include "constants.h"
#include "Textures.h"
#include "Projectile.h"
#include <iostream>

Level1::Level1()
{
	//entities.push_back(new Player(textures::texture, sf::Vector2f(100, WINDOWHEIGHT - 100), PLAYERSPEED));
	textures::setTextures();
	player = new Player(textures::playerTexture, sf::Vector2f(100, WINDOWHEIGHT - 100));
	cooldown = 1;
}

void Level1::draw(sf::RenderWindow& window)
{
	window.draw(player->getSprite());
	for (Entity* proj : projectiles)
	{
		window.draw(proj->getSprite());
	}
}

void Level1::update(float time)
{
	std::cout << time << std::endl;
	for (Entity* proj: projectiles)
	{
		proj->update(time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player->update(-PLAYERSPEED, time);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player->update(PLAYERSPEED, time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (cooldown >= 300) {
			Projectile* projectile = new Projectile(textures::projectileTexture, player->pos);
			projectiles.push_back(projectile);
			cooldown = 1;
		}
	}
	cooldown+=time;
}