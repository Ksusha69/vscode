#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape eyeball;
    sf::ConvexShape pupil;

    sf::Vector2f position;

    float rotation = 0;
};

double isInside(const sf::Vector2f &mousePosition, const sf::Vector2f &center, float X, float Y)
{
    return ((std::pow(mousePosition.x - center.x, 2) / std::pow(X, 2)) + (std::pow(mousePosition.y - center.y, 2) / std::pow(Y, 2)));
}

// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidian(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * float(cos(angle)),
        radiusY * float(sin(angle))};
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обновляет состояние глаза
void updateEye1(Eye &eye1)
{
    const sf::Vector2f rotationRadius = {50.f, 90.f};
    const sf::Vector2f eyeball1Offset = toEuclidian(rotationRadius.x, rotationRadius.y, eye1.rotation);
    eye1.pupil.setPosition(eye1.position + eyeball1Offset);
}

// Обновляет состояние глаза
void updateEye2(Eye &eye2)
{
    const sf::Vector2f rotationRadius = {50.f, 90.f};
    const sf::Vector2f eyeball2Offset = toEuclidian(rotationRadius.x, rotationRadius.y, eye2.rotation);
    eye2.pupil.setPosition(eye2.position + eyeball2Offset);
}

// Инициализирует глаз
void initEyes(Eye &eye1, Eye &eye2)
{
    const sf::Vector2f eyeballRadius = {80.f, 140.f};
    const sf::Vector2f pupilRadius = {25.f, 40.f};
    constexpr int pointCount = 200;

    eye1.position = {300, 300};
    eye2.position = {500, 300};

    eye1.eyeball.setPosition(eye1.position);
    eye1.eyeball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye1.eyeball.setPointCount(pointCount);
    eye2.eyeball.setPosition(eye2.position);
    eye2.eyeball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye2.eyeball.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyeballRadius.x * std::sin(angle),
            eyeballRadius.y * std::cos(angle)};
        eye1.eyeball.setPoint(pointNo, point);
        eye2.eyeball.setPoint(pointNo, point);
    }

    eye1.pupil.setPointCount(pointCount);
    eye1.pupil.setFillColor(sf::Color(0x00, 0x00, 0x00));
    eye2.pupil.setPointCount(pointCount);
    eye2.pupil.setFillColor(sf::Color(0x00, 0x00, 0x00));
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * std::sin(angle),
            pupilRadius.y * std::cos(angle)};
        eye1.pupil.setPoint(pointNo, point);
        eye2.pupil.setPoint(pointNo, point);
    }

    updateEye1(eye1);
    updateEye2(eye2);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле
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

// Обновляет зрачки, указывающие на мышь
void updateEyes(const sf::Vector2f &mousePosition, Eye &eye1, Eye &eye2)
{
    const sf::Vector2f radXY = {50.f, 90.f};

    const double isInsideEye1 = isInside(mousePosition,
                                         eye1.eyeball.getPosition(),
                                         radXY.x,
                                         radXY.y);

    const double isInsideEye2 = isInside(mousePosition,
                                         eye2.eyeball.getPosition(),
                                         radXY.x,
                                         radXY.y);

    if (isInsideEye1 > 1.f)
    {
        const sf::Vector2f leftEyeDelta = mousePosition - eye1.position;
        eye1.rotation = atan2(leftEyeDelta.y, leftEyeDelta.x);
        updateEye1(eye1);
    }
    else
    {
        eye1.pupil.setPosition(mousePosition);
    }

    if (isInsideEye2 > 1.f)
    {
        const sf::Vector2f rightEyeDelta = mousePosition - eye2.position;
        eye2.rotation = atan2(rightEyeDelta.y, rightEyeDelta.x);
        updateEye2(eye2);
    }
    else
    {
        eye2.pupil.setPosition(mousePosition);
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &eye1, Eye &eye2)
{
    window.clear();
    window.draw(eye1.eyeball);
    window.draw(eye1.pupil);
    window.draw(eye2.eyeball);
    window.draw(eye2.pupil);
    window.display();
}

// Программа рисует в окне глаза, у которых зрачки поворачиваются вслед за курсором мыши
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eyes follows mouse", sf::Style::Default, settings);

    Eye eye1;
    Eye eye2;
    sf::Vector2f mousePosition;

    initEyes(eye1, eye2);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateEyes(mousePosition, eye1, eye2);
        redrawFrame(window, eye1, eye2);
    }
}