#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {80, 0});
    pointer.setPoint(1, {-40, -40});
    pointer.setPoint(2, {-40, 40});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xF0, 0xA0, 0x00));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}

void pollEvent(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float &dt)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float maxRotation = 15 * dt;
    const float rotation = std::abs((angle - pointer.getRotation()));
    if (angle != pointer.getRotation())
    {
        if (angle > pointer.getRotation())
        {
            if ((angle - 180) > pointer.getRotation())
            {
                pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
            }
        }
        else
        {
            if ((angle + 180) < pointer.getRotation())
            {
                pointer.setRotation(pointer.getRotation() + std::min(maxRotation, rotation));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() - std::min(maxRotation, rotation));
            }
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Clock clock;

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        pollEvent(window, mousePosition);
        float dt = clock.restart().asSeconds();
        update(mousePosition, pointer, dt);
        redrawFrame(window, pointer);
    }
}