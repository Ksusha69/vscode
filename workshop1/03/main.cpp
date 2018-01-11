#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

int main()
{
    // окно
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Texture texture;
    texture.loadFromFile("cat/cat.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(400, 300);

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Cat");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color(255, 255, 255));
        window.draw(sprite);
        window.display();
    }
}