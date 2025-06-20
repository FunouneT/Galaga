#pragma once
#include <SFML/Graphics.hpp>

enum class State { Idle, Sprint };
enum class Direction { Left, Down, Right };

class Entity{
public:

	Direction direction;

	State state;
	sf::Vector2f pos;
	sf::Sprite sprite;
	sf::Texture texture;

	Entity(sf::Texture&, sf::Vector2f);

	sf::Sprite getSprite();
	sf::Vector2f getPos();
	bool collide(Entity&);

	virtual void update();
	virtual void update(float);
	virtual void update(sf::Vector2f, float);
	virtual void update(float, float);
	virtual ~Entity();
};

