#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({350, 300}), "Home");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({200, 170});
    shape1.setPosition({80, 150});
    shape1.setFillColor(sf::Color(0x8B, 0x45, 0x13));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({50, 120});
    shape2.setPosition({110, 200});
    shape2.setFillColor(sf::Color(0x00, 0x00, 0x80));
    window.draw(shape2);

    sf::ConvexShape trapeze;
    trapeze.setFillColor(sf::Color(0x80, 0x00, 0x00));
    trapeze.setPosition({30, 100});
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {80, 0});
    trapeze.setPoint(1, {220, 0});
    trapeze.setPoint(2, {270, 50});
    trapeze.setPoint(3, {30, 50});
    window.draw(trapeze);

    sf::RectangleShape shape3;
    shape3.setSize({20, 40});
    shape3.setPosition({200, 90});
    shape3.setFillColor(sf::Color(0x70, 0x80, 0x80));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({40, 20});
    shape4.setPosition({190, 70});
    shape4.setFillColor(sf::Color(0x70, 0x80, 0x80));
    window.draw(shape4);

    sf::CircleShape shape5(8);
    shape5.setPosition({210, 54});
    shape5.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(shape5);

    sf::CircleShape shape6(9);
    shape6.setPosition({212, 40});
    shape6.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(shape6);

    sf::CircleShape shape7(11);
    shape7.setPosition({215, 23});
    shape7.setFillColor(sf::Color(0xC0, 0xC0, 0xC0));
    window.draw(shape7);

    window.display();

    sf::sleep(sf::seconds(5));
}