#pragma once

#include <SFML/Graphics.hpp>

enum class Direction { Left, Down, Right };

class Entity
{
public:

	Direction direction;

	sf::Vector2f pos;

	sf::Sprite sprite;

	sf::Texture texture;

	//float speed;

	Entity(sf::Texture&, sf::Vector2f);

	//Entity();

	sf::Sprite getSprite();

	sf::Vector2f getPos();

	bool collide(Entity&);

	virtual void update();

	virtual void update(float);

	virtual void update(sf::Vector2f, float);

	virtual void update(float, float);

	virtual ~Entity();
};

