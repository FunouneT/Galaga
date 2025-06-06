#include "Level1.h"
#include "Player.h"
#include "constants.h"
#include "Textures.h"
#include "Projectile.h"
#include "Enemy.h"
#include <iostream>
//Конструктор класса
Level1::Level1()
{
	//Устанавливаем ВСЕ текстурки
	textures::setTextures();
	//Создаём динамически игрока
	player = new Player(textures::playerTexture, sf::Vector2f(100, WINDOWHEIGHT - 100));
	//Задаём начальное значение кулдаунов
	projectileCD = 0;
	enemySpawnCD = 0;
	countOfEnemies = 0;
}
//--------------------------------------------------------------------------------------------
//Метод отрисовки всего, что находится в игре
void Level1::draw(sf::RenderWindow& window)
{
	//Отрисовываем игрока методом класса RenderWindow из SFML, получив спрайт игрока
	window.draw(player->getSprite());
	//Отрисовываем все снаряды
	for (Entity* proj : projectiles)
	{
		window.draw(proj->getSprite());
	}
	//Отрисовываем всех врагов
	for (Entity* enem : enemies)
	{
		window.draw(enem->getSprite());
	}
}
//--------------------------------------------------------------------------------------------
//Метод обновления всего, что находится в игре
void Level1::update(float time)
{
	//--------------------------------------------------------------------------------------------
	//Обновление снарядов
	for (Entity* proj : projectiles)
	{
		proj->update(time);
	}
	//--------------------------------------------------------------------------------------------
	//Обновление/управление игрока
	//Если клавиша "стрелка влево" нажата, то обновляем игрока соответственно
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		player->state = State::Sprint;
	else
		player->state = State::Idle;
	//std::cout << (player->state == State::Idle ? 0 : 1) << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player->update((player->state == State::Sprint ? -PLAYERSPEED * 1.5 : -PLAYERSPEED), time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player->update((player->state == State::Sprint ? PLAYERSPEED * 1.5 : PLAYERSPEED), time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//Если кулдаун "накопился достаточно", то позволяем создать снаряд
		if (projectileCD >= PROJCD) {
			//Создаём динамически снаряд, передаём его текстурку и позицию игрока
			Projectile* projectile = new Projectile(textures::projectileTexture, player->getPos());
			//Записываем созданный объект в лист
			projectiles.push_back(projectile);
			//Сбрасываем кулдаун (нужно будет переделать систему, т.к. возможно переполнение переменной)
			projectileCD = 0;
		}
	}
	//--------------------------------------------------------------------------------------------
	//Создание противников
	if (enemySpawnCD >= ENEMSPAWNCD and countOfEnemies < 20) {
		Enemy* enemy = new Enemy(textures::enemyTexture, sf::Vector2f(WINDOWWIDTH - 60, 40));
		enemies.push_back(enemy);
		enemy->direction = Direction::Left;
		enemySpawnCD = 0;
		countOfEnemies++;
	}
	//--------------------------------------------------------------------------------------------
	//Обновление противников
	//Проходимся по листу врагов
	for (Entity* enem : enemies)
	{
		if (rand() % 3000 == 1)
			enem->state = State::Sprint;
		if (enem->state == State::Idle) {
			//Если левая граница преодолена, то
			if (enem->getPos().x <= 0) {
				//Меняем направление противника
				enem->direction = Direction::Right;
				//Толкаем вниз на следующую строку и чуть вправо, чтобы он ещё раз не ушёл вниз
				enem->update(sf::Vector2f(0.05, 80 / time), time);
			}
			//Соответственно с правой границей, -60 - временная заглушка, чтобы текстура врага не уходила за экран
			if (enem->getPos().x > WINDOWWIDTH - 60) {
				enem->direction = Direction::Left;
				enem->update(sf::Vector2f(-0.05, 80 / time), time);
			}


			//Двигаем врагов согласно направлению
			if (enem->direction == Direction::Left)
				enem->update(sf::Vector2f(-ENEMYSPEED, 0), time);
			if (enem->direction == Direction::Right)
				enem->update(sf::Vector2f(ENEMYSPEED, 0), time);
		}
		else {
			enem->update(sf::Vector2f(0, ENEMYSPEED * 1.5), time);
		}
	}
	//--------------------------------------------------------------------------------------------
	//Коллизия снарядов и противников
	//Если листы снарядов и врагов не пустые, то
	if (!projectiles.empty() and !enemies.empty()) {
		//Проходимся по листу врагов, i - итератор листа
		for (auto i = enemies.begin(); i != enemies.end();)
		{
			bool enemyIsDead = false;
			//Объявляем указатель на врага, чтобы с ним работать
			Entity* enem = *i;
			//Проходимся по листу снарядов, j - итератор листа
			for (auto j = projectiles.begin(); j != projectiles.end();)
			{
				//Объявляем указатель на снаряд, чтобы с ним работать
				Entity* proj = *j;
				//Если есть коллизия врага и снаряда
				if (enem->collide(*proj)) {
					//Удаляем из списка соприкоснувшиеся элементы
					//И записываем в i и j элементы, следующие за удалёнными
					i = enemies.erase(i);
					j = projectiles.erase(j);
					//Вызываем соответствующие деструкторы
					enem->~Entity();
					proj->~Entity();
					enemyIsDead = true;
					break;
				}
				//Если коллизии не было, то идём дальше по листу
				else j++;
			}
			//Если коллизии не было, то идём дальше по листу
			if (!enemyIsDead) i++;
		}
	}
	//--------------------------------------------------------------------------------------------
	//Обновление кулдаунов
	projectileCD += time;
	enemySpawnCD += time;
}