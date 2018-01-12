#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <cassert>

constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned WINDOW_WIDTH = 800;

constexpr unsigned BALL_SIZE = 50;

struct Balls
{
    sf::CircleShape shapes;
    sf::Vector2f speed;
    sf::Vector2f position;
    sf::Clock clock;
    float time = 0;
};

struct PRNG
{
    unsigned seed = 0;
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    generator.seed = unsigned(std::time(nullptr));
}

unsigned getRandomSpeed(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);
    generator.seed = (generator.seed * 73129 + 95121);
    return (generator.seed % (maxValue + 1 - minValue)) + minValue;
}

float getRandomColor(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 255);
    return distribution(generator.engine);
}

void init(std::vector<Balls> &balls)
{
    const std::vector<sf::Color> colors = {
        sf::Color(255, 51, 0),
        sf::Color(204, 102, 51),
        sf::Color(0, 51, 255),
        sf::Color(0, 153, 0),
        sf::Color(102, 0, 51),
        sf::Color(102, 255, 153),
        sf::Color(122, 255, 255),
        sf::Color(153, 0, 51)};

    const std::vector<sf::Vector2f> positions = {
        {10, 10},
        {110, 110},
        {210, 210},
        {310, 310},
        {410, 410}};

    PRNG generator;
    initGenerator(generator);
    sf::Color color;

    for (size_t i = 0; i < balls.size(); ++i)
    {
        float minSpeed = getRandomSpeed(generator, 0.f, 700.f);
        float maxSpeed = getRandomSpeed(generator, 0.f, 700.f);

        color.r = (getRandomColor(generator) + getRandomColor(generator)) / 2;
        color.g = (getRandomColor(generator) + getRandomColor(generator)) / 2;
        color.b = (getRandomColor(generator) + getRandomColor(generator)) / 2;

        balls[i].speed = {minSpeed, maxSpeed};
        balls[i].shapes.setPosition(positions[i]);
        balls[i].shapes.setRadius(BALL_SIZE);
        balls[i].shapes.setFillColor(color);
        balls[i].shapes.setOrigin(BALL_SIZE, BALL_SIZE);
    }
}

void initBall(std::vector<Balls> &balls, PRNG &generator, sf::Vector2f &clickPosition)
{
    Balls ball;
    balls.push_back(ball);
    sf::Color color;

    const std::vector<sf::Color> colors = {
        sf::Color(255, 51, 0),
        sf::Color(204, 102, 51),
        sf::Color(0, 51, 255),
        sf::Color(0, 153, 0),
        sf::Color(102, 0, 51),
        sf::Color(102, 255, 153),
        sf::Color(122, 255, 255),
        sf::Color(153, 0, 51)};

    float minSpeed = getRandomSpeed(generator, 0.f, 700.f);
    float maxSpeed = getRandomSpeed(generator, 0.f, 700.f);

    color.r = (getRandomColor(generator) + getRandomColor(generator)) / 2;
    color.g = (getRandomColor(generator) + getRandomColor(generator)) / 2;
    color.b = (getRandomColor(generator) + getRandomColor(generator)) / 2;

    size_t i = balls.size() - 1;
    balls[i].speed = {minSpeed, maxSpeed};
    balls[i].shapes.setPosition(clickPosition);
    balls[i].shapes.setRadius(BALL_SIZE);
    balls[i].shapes.setFillColor(color);
    balls[i].shapes.setOrigin(BALL_SIZE, BALL_SIZE);
}

void onMouseClick(sf::Event::MouseButtonEvent &event, sf::Vector2f &clickPosition)
{
    clickPosition = {static_cast<float>(event.x), static_cast<float>(event.y)};
}

bool ballNotInBall(std::vector<Balls> &balls, sf::Vector2f &clickPosition)
{
    bool value = true;
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f deltaBall = balls[i].shapes.getPosition() - clickPosition;
        float delta = hypot(deltaBall.x, deltaBall.y);
        if (delta <= 2 * BALL_SIZE)
        {
            value = false;
        }
    }
    return value;
}

void pollEvents(sf::RenderWindow &window, std::vector<Balls> &balls, PRNG &generator, sf::Vector2f &clickPosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, clickPosition);
            if (ballNotInBall(balls, clickPosition))
            {
                initBall(balls, generator, clickPosition);
            }
            break;
        default:
            break;
        }
    }
}

auto removeBalls(Balls ball)
{
    return (ball.time >= 10);
}

auto removeDeathBalls(std::vector<Balls> &balls)
{
    balls.erase(std::remove_if(balls.begin(), balls.end(), removeBalls), balls.end());
}

void updateBallLifetimes(std::vector<Balls> &balls, size_t i)
{
    balls[i].time = balls[i].clock.getElapsedTime().asSeconds();
}

bool areCloseAbsolute(float a, float b, float tolerance = 0.001f)
{
    return std::abs(a - b) < tolerance;
}

bool areCloseRelative(float a, float b, float tolerance = 0.001f)
{
    return std::abs((a - b) / b) < tolerance;
}

bool areFuzzyEqual(float a, float b)
{
    constexpr float tolerance = 0.001f;
    if (std::abs(b) > 1.f)
    {
        return areCloseRelative(a, b, tolerance);
    }
    return areCloseAbsolute(a, b, tolerance);
}

bool areVectorsFuzzyEqual(sf::Vector2f a, sf::Vector2f b)
{
    bool areXEqual = areFuzzyEqual(a.x, b.x);
    bool areYEqual = areFuzzyEqual(a.y, b.y);
    return (areXEqual && areYEqual);
}

float lawOfEnergyConservation(sf::Vector2f speed1, sf::Vector2f speed2)
{
    return std::pow(hypot(speed1.x, speed1.y), 2) + std::pow(hypot(speed2.x, speed2.y), 2);
}

float lawOfImpulsConservation(sf::Vector2f speed1, sf::Vector2f speed2)
{
    sf::Vector2f sumVectors = speed1 + speed2;
    return hypot(sumVectors.x, sumVectors.y);
}

void updateBalls(std::vector<Balls> &balls)
{
    for (size_t i = 0; i < balls.size(); ++i)
    {
        for (size_t j = i + 1; j < balls.size(); ++j)
        {

            sf::Vector2f deltaPosition1 = balls[i].shapes.getPosition() - balls[j].shapes.getPosition();
            float distanceMin1 = hypot(deltaPosition1.x, deltaPosition1.y);
            float distanceMax = BALL_SIZE * 2;
            if (distanceMin1 <= distanceMax)
            {
                float oldLawOfEnergyConservation = lawOfEnergyConservation(balls[i].speed, balls[j].speed);
                float oldLawOfImpulsConservation = lawOfImpulsConservation(balls[i].speed, balls[j].speed);

                sf::Vector2f deltaSpeed1 = balls[i].speed - balls[j].speed;
                float scalar1 = deltaPosition1.x * deltaSpeed1.x + deltaPosition1.y * deltaSpeed1.y;

                sf::Vector2f deltaSpeed2 = balls[j].speed - balls[i].speed;
                sf::Vector2f deltaPosition2 = balls[j].shapes.getPosition() - balls[i].shapes.getPosition();
                float distanceMin2 = hypot(deltaPosition2.x, deltaPosition2.y);
                float scalar2 = deltaPosition2.x * deltaSpeed2.x + deltaPosition2.y * deltaSpeed2.y;

                balls[i].speed = balls[i].speed - scalar1 * deltaPosition1 / float(std::pow(distanceMin1, 2));
                balls[j].speed = balls[j].speed - scalar2 * deltaPosition2 / float(std::pow(distanceMin2, 2));

                float newLawOfEnergyConservation = lawOfEnergyConservation(balls[i].speed, balls[j].speed);
                float newLawOfImpulsConservation = lawOfImpulsConservation(balls[i].speed, balls[j].speed);
                assert(areFuzzyEqual(oldLawOfEnergyConservation, newLawOfEnergyConservation));
                assert(areFuzzyEqual(oldLawOfImpulsConservation, newLawOfImpulsConservation));
            }
        }
    }
}

void update(std::vector<Balls> &balls, float dt)
{
    float intervalDt = dt / 10;
    for (size_t i = 0; i < 10; ++i)
    {
        removeDeathBalls(balls);
        updateBalls(balls);

        for (size_t i = 0; i < balls.size(); ++i)
        {
            sf::Vector2f position = balls[i].shapes.getPosition();
            position += balls[i].speed * intervalDt;

            if ((position.x + BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
            {
                balls[i].speed.x = -balls[i].speed.x;
            }
            if ((position.x - BALL_SIZE < 0) && (balls[i].speed.x < 0))
            {
                balls[i].speed.x = -balls[i].speed.x;
            }
            if ((position.y + BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
            {
                balls[i].speed.y = -balls[i].speed.y;
            }
            if ((position.y - BALL_SIZE < 0) && (balls[i].speed.y < 0))
            {
                balls[i].speed.y = -balls[i].speed.y;
            }
            balls[i].shapes.setPosition(position);
            updateBallLifetimes(balls, i);
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Balls> &balls)
{
    window.clear();
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].shapes);
    }
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Balls");
    sf::Clock clock;

    PRNG generator;
    initGenerator(generator);

    std::vector<Balls> balls(5);
    sf::Vector2f clickPosition = {0, 0};

    init(balls);

    while (window.isOpen())
    {
        pollEvents(window, balls, generator, clickPosition);
        float dt = clock.restart().asSeconds();
        update(balls, dt);
        redrawFrame(window, balls);
    }
}