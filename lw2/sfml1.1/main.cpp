#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({140, 380}), "Svetofor");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({120, 360});
    shape1.setRotation(0);
    shape1.setPosition({10, 10});
    shape1.setFillColor(sf::Color(0x69, 0x69, 0x69));
    window.draw(shape1);

    sf::CircleShape shape2(55);
    shape2.setPosition({15, 15});
    shape2.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(55);
    shape3.setPosition({15, 135});
    shape3.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(shape3);

    sf::CircleShape shape4(55);
    shape4.setPosition({15, 255});
    shape4.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}