#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    const float maxAngleInSecond = 90;
    float angle = atan2(delta.y, delta.x);
    const float maxRotationSpeed = maxAngleInSecond * deltaTime;
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }
    float rotationAngle = toDegrees(angle) - arrow.getRotation();
    float rotationSpeed = std::abs(rotationAngle) * deltaTime;
    if (rotationAngle != 0)
    {
        if (rotationAngle > 0)
        {
            if ((rotationAngle - 180) > 0)
            {
                arrow.setRotation(arrow.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
            }
        }
        else
        {
            if ((rotationAngle + 180) < 0)
            {
                arrow.setRotation(arrow.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
            }
            else
            {
                arrow.setRotation(arrow.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
            }
        }
    }
    const float distanceFromCursor = std::sqrt((delta.x * delta.x) + (delta.y * delta.y));
    sf::Vector2f direction = {0.f, 0.f};
    if (distanceFromCursor != 0)
    {
        direction = {delta.x / distanceFromCursor, delta.y / distanceFromCursor};
    }
    const float maxMovementSpeed = 20.f;
    const float movementSpeed = maxMovementSpeed * deltaTime;
    arrow.setPosition(arrow.getPosition() + direction * movementSpeed);
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(arrow);
    window.display();
}
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned ANTIALIASING_LEVEL = 8;

    sf::Clock clock;
    sf::Vector2f mousePosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Arrow with borders", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    arrow.setPosition({400, 300});
    arrow.setFillColor(sf::Color{255, 255, 0});
    arrow.setPointCount(7);
    arrow.setPoint(0, {0, 60});
    arrow.setPoint(1, {60, 0});
    arrow.setPoint(2, {0, -60});
    arrow.setPoint(3, {0, -30});
    arrow.setPoint(4, {-60, -30});
    arrow.setPoint(5, {-60, 30});
    arrow.setPoint(6, {0, 30});
    arrow.setOutlineColor(sf::Color{0, 0, 0});
    arrow.setOutlineThickness(2);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, arrow, deltaTime);
        redrawFrame(window, arrow);
    }
}