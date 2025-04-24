#include "Entity.h"

Entity::Entity(sf::Texture& texture, sf::Vector2f pos)
{
	//������� � ����� ������� � ��������
	this->pos = pos;
	this->texture = texture;
	//���������� ���������� � ������ ��������
	sprite.setTexture(this->texture);
	sprite.setPosition(this->pos);
}
//�������
sf::Sprite Entity::getSprite()
{
	return sprite;
}

sf::Vector2f Entity::getPos()
{
	return pos;
}
//����������
Entity::~Entity()
{

}
//��������� �������� ������� ��� ��������
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
//�������� (������������ ����� intersects �� SFML, ���� ����� ������� ����)
bool Entity::collide(Entity& entity)
{
	return sprite.getGlobalBounds().intersects(entity.getSprite().getGlobalBounds());
}
