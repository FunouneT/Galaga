#include "constants.h"
#include "Level1.h"

int main()
{
    //������ ����
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Galaga game");
    //������ ������
    sf::Clock clock;
    //������ �������, ������
    Level1 level1;
    //���� ���� �������
    while (window.isOpen())
    {
        //��� �� ����� ���� �� ��������
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 300;
        //���������, ����� �� ������� �������� ����
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                //���� �����, �� ��������� ����, ��������� ���������
                window.close();
        }
        //��������� �������
        level1.update(time);
        //������� ���� �� ����������� �����
        window.clear();
        //������������ �������
        level1.draw(window);
        //���������� �� �� ����
        window.display();
    }

    return 0;
}