#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <cassert>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

constexpr unsigned BALL_SIZE = 50;

struct Balls
{
    sf::CircleShape shapes;
    sf::Vector2f position;
    sf::Vector2f speed;
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
    }
}

void updateBalls(std::vector<Balls> &balls)
{
    for (size_t i = 0; i < balls.size(); ++i)
    {
        for (size_t j = i + 1; j < balls.size(); ++j)
        {
            sf::Vector2f deltaPosition = balls[i].shapes.getPosition() - balls[j].shapes.getPosition();
            float distanceMin = hypot(deltaPosition.x, deltaPosition.y); //Сумма квадратов и всё это под корнем
            float distanceMax = BALL_SIZE * 2;
            if (distanceMin <= distanceMax)
            {
                sf::Vector2f deltaSpeed = balls[i].speed - balls[j].speed;
                float scalar = deltaPosition.x * deltaSpeed.x + deltaPosition.y * deltaSpeed.y;
                balls[i].speed = balls[i].speed - scalar * deltaPosition / float(std::pow(distanceMin, 2));
                balls[j].speed = balls[j].speed + scalar * deltaPosition / float(std::pow(distanceMin, 2));
            }
        }
    }
}

void update(std::vector<Balls> &balls, float dt)
{
    updateBalls(balls);

    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shapes.getPosition();
        position += balls[i].speed * dt;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        balls[i].shapes.setPosition(position);
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
    sf::RenderWindow window(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Balls", sf::Style::Default, settings);
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