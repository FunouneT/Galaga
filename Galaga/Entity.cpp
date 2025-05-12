#include "Entity.h"

Entity::Entity(sf::Texture& texture, sf::Vector2f pos)
{
	//Передаём в класс позицию и текстуру
	this->pos = pos;
	this->texture = texture;
	//Записываем переданное в спрайт сущности
	sprite.setTexture(this->texture);
	sprite.setPosition(this->pos);
}
//Геттеры
sf::Sprite Entity::getSprite()
{
	return sprite;
}

sf::Vector2f Entity::getPos()
{
	return pos;
}
//Деструктор
Entity::~Entity()
{

}
//Различные вариации апдейта для потомков
void Entity::update()
{

}

void Entity::update(float time)
{

}

void Entity::update(sf::Vector2f, float time)
{

}

void Entity::update(float speed, float time)
{

}
//Коллизия (используется метод intersects из SFML, хотя можно сделать свой)
bool Entity::collide(Entity& entity)
{
	return sprite.getGlobalBounds().intersects(entity.getSprite().getGlobalBounds());
}
