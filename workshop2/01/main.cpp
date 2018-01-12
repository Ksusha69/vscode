#include <SFML/Graphics.hpp>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

constexpr float BALL_SIZE = 50;

struct Balls
{
    sf::CircleShape shapes;
    sf::Vector2f position;
    sf::Vector2f speed;
};

void init(std::vector<Balls> &balls)
{
    const std::vector<sf::Color> colors = {
        sf::Color(0xFF, 0X7F, 0x50),
        sf::Color(0xDC, 0x14, 0x3C),
        sf::Color(0x00, 0x00, 0x8B),
        sf::Color(0x00, 0xFF, 0xFF),
        sf::Color(0x7F, 0xFF, 0x00)};
    const std::vector<sf::Vector2f> speeds = {
        {80.f, 80.f},
        {130.f, 130.f},
        {180.f, 180.f},
        {230.f, 230.f},
        {280.f, 280.f}};
    const std::vector<sf::Vector2f> positions = {
        {10, 10},
        {70, 70},
        {130, 130},
        {190, 190},
        {250, 250}};
    for (size_t i = 0; i < balls.size(); ++i)
    {
        balls[i].speed = speeds[i];
        balls[i].shapes.setPosition(positions[i]);
        balls[i].shapes.setRadius(BALL_SIZE);
        balls[i].shapes.setFillColor(colors[i]);
    }
}

void update(std::vector<Balls> &balls, float &dt)
{
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

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
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
    sf::RenderWindow window(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Balls");
    sf::Clock clock;

    std::vector<Balls> balls(5);
    init(balls);

    while (window.isOpen())
    {
        pollEvents(window);
        float dt = clock.restart().asSeconds();
        update(balls, dt);
        redrawFrame(window, balls);
    }
}