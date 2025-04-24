#include "constants.h"
#include "Level1.h"

int main()
{
    //Создаём окно
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Galaga game");
    //Создаём таймер
    sf::Clock clock;
    //Создаём уровень, первый
    Level1 level1;
    //Пока окно открыто
    while (window.isOpen())
    {
        //Вот по этому пока не подскажу
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 300;
        //Проверяем, нажат ли крестик закрытия окна
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                //Если нажат, то закрываем окно, завершаем программу
                window.close();
        }
        //Обновляем уровень
        level1.update(time);
        //Очищаем окно от предыдущего кадра
        window.clear();
        //Отрисовываем уровень
        level1.draw(window);
        //Отображаем всё на окне
        window.display();
    }

    return 0;
}