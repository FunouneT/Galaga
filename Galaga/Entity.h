#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:

	sf::Vector2f pos;

	sf::Sprite sprite;

	sf::Texture texture;

	//float speed;

	Entity(sf::Texture&, sf::Vector2f);

	//Entity();

	sf::Sprite getSprite();

	sf::Vector2f getPos();

	virtual void update();

	virtual void update(float);

	virtual void update(float, float);

	virtual ~Entity();
};

