#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned ANTIALIASING_LEVEL = 8;

    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Arrow with borders", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    arrow.setPosition({400, 300});
    arrow.setFillColor(sf::Color{255, 255, 0});
    arrow.setPointCount(7);
    arrow.setPoint(0, {0, -50});
    arrow.setPoint(1, {-50, 0});
    arrow.setPoint(2, {-30, 0});
    arrow.setPoint(3, {-30, 60});
    arrow.setPoint(4, {30, 60});
    arrow.setPoint(5, {30, 0});
    arrow.setPoint(6, {50, 0});
    arrow.setOutlineColor(sf::Color{0, 0, 0});
    arrow.setOutlineThickness(2);

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
        window.draw(arrow);
        window.display();
    }
}