#include "Level1.h"
#include "Player.h"
#include "constants.h"
#include "Textures.h"
#include "Projectile.h"
#include "Enemy.h"
#include <iostream>
//����������� ������
Level1::Level1()
{
	//������������� ��� ���������
	textures::setTextures();
	//������ ����������� ������
	player = new Player(textures::playerTexture, sf::Vector2f(100, WINDOWHEIGHT - 100));
	//����� ��������� �������� ���������
	projectileCD = 0;
	enemySpawnCD = 0;
	countOfEnemies = 0;
}
//--------------------------------------------------------------------------------------------
//����� ��������� �����, ��� ��������� � ����
void Level1::draw(sf::RenderWindow& window)
{
	//������������ ������ ������� ������ RenderWindow �� SFML, ������� ������ ������
	window.draw(player->getSprite());
	//������������ ��� �������
	for (Entity* proj : projectiles)
	{
		window.draw(proj->getSprite());
	}
	//������������ ���� ������
	for (Entity* enem : enemies)
	{
		window.draw(enem->getSprite());
	}
}
//--------------------------------------------------------------------------------------------
//����� ���������� �����, ��� ��������� � ����
void Level1::update(float time)
{
	//--------------------------------------------------------------------------------------------
	//���������� ��������
	for (Entity* proj : projectiles)
	{
		proj->update(time);
	}
	//--------------------------------------------------------------------------------------------
	//����������/���������� ������
	//���� ������� "������� �����" ������, �� ��������� ������ ��������������
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player->update(-PLAYERSPEED, time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player->update(PLAYERSPEED, time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//���� ������� "��������� ����������", �� ��������� ������� ������
		if (projectileCD >= 300) {
			//������ ����������� ������, ������� ��� ��������� � ������� ������
			Projectile* projectile = new Projectile(textures::projectileTexture, player->getPos());
			//���������� ��������� ������ � ����
			projectiles.push_back(projectile);
			//���������� ������� (����� ����� ���������� �������, �.�. �������� ������������ ����������)
			projectileCD = 0;
		}
	}
	//--------------------------------------------------------------------------------------------
	//�������� �����������
	if (enemySpawnCD >= 2000 and countOfEnemies < 20) {
		Enemy* enemy = new Enemy(textures::enemyTexture, sf::Vector2f(WINDOWWIDTH - 60, 40));
		enemies.push_back(enemy);
		enemy->direction = Direction::Left;
		enemySpawnCD = 0;
		countOfEnemies++;
	}
	//--------------------------------------------------------------------------------------------
	//���������� �����������
	//���������� �� ����� ������
	for (Entity* enem : enemies)
	{
		//���� ����� ������� ����������, ��
		if (enem->getPos().x <= 0) {
			//������ ����������� ����������
			enem->direction = Direction::Right;
			//������� ���� �� ��������� ������ � ���� ������, ����� �� ��� ��� �� ���� ����
			enem->update(sf::Vector2f(0.05, 80 / time), time);
		}
		//�������������� � ������ ��������, -60 - ��������� ��������, ����� �������� ����� �� ������� �� �����
		if (enem->getPos().x > WINDOWWIDTH - 60) {
			enem->direction = Direction::Left;
			enem->update(sf::Vector2f(-0.05, 80 / time), time);
		}


		//������� ������ �������� �����������
		if (enem->direction == Direction::Left)
			enem->update(sf::Vector2f(-0.05, 0), time);
		if (enem->direction == Direction::Right)
			enem->update(sf::Vector2f(0.05, 0), time);
	}
	//--------------------------------------------------------------------------------------------
	//�������� �������� � �����������
	//���� ����� �������� � ������ �� ������, ��
	if (!projectiles.empty() and !enemies.empty()) {
		//���������� �� ����� ������, i - �������� �����
		for (auto i = enemies.begin(); i != enemies.end();)
		{
			bool enemyIsDead = false;
			//��������� ��������� �� �����, ����� � ��� ��������
			Entity* enem = *i;
			//���������� �� ����� ��������, j - �������� �����
			for (auto j = projectiles.begin(); j != projectiles.end();)
			{
				//��������� ��������� �� ������, ����� � ��� ��������
				Entity* proj = *j;
				//���� ���� �������� ����� � �������
				if (enem->collide(*proj)) {
					//������� �� ������ ���������������� ��������
					//� ���������� � i � j ��������, ��������� �� ���������
					i = enemies.erase(i);
					j = projectiles.erase(j);
					//�������� ��������������� �����������
					enem->~Entity();
					proj->~Entity();
					enemyIsDead = true;
					break;
				}
				//���� �������� �� ����, �� ��� ������ �� �����
				else j++;
			}
			//���� �������� �� ����, �� ��� ������ �� �����
			if (!enemyIsDead) i++;
		}
	}
	//--------------------------------------------------------------------------------------------
	//���������� ���������
	projectileCD += time;
	enemySpawnCD += time;
}