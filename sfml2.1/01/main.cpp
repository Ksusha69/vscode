#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 900;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 48;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Simple Event Loop");
    sf::Clock clock;

    const sf::Vector2f position = {15, 250};
    float time = 0;
    float speedX = 100.f;
    float x = 0;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xA0, 0x52, 0x2D));

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

        constexpr float amplitudeY = 100.f;
        constexpr float periodY = 3;

        const float dt = clock.restart().asSeconds();
        time += dt;
        const float wavePhase = time * float(2 * M_PI);
        x = x + speedX * dt;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};

        ball.setPosition(position + offset);

        sf::Vector2f position = ball.getPosition();

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        ball.setPosition(position);

        window.clear();
        window.draw(ball);
        window.display();
    }
}