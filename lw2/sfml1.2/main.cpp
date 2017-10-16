#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({450, 200}), "MKA");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({30, 160});
    shape1.setRotation(0);
    shape1.setPosition({20, 20});
    shape1.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({30, 85});
    shape2.setOrigin({50, 20});
    shape2.setRotation(-45);
    shape2.setPosition({78, 20});
    shape2.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({30, 85});
    shape3.setRotation(45);
    shape3.setPosition({130, 20});
    shape3.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({30, 160});
    shape4.setRotation(0);
    shape4.setPosition({130, 20});
    shape4.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({30, 160});
    shape5.setRotation(0);
    shape5.setPosition({180, 20});
    shape5.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({80, 30});
    shape6.setRotation(-45);
    shape6.setPosition({201, 80});
    shape6.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({110, 30});
    shape7.setRotation(45);
    shape7.setPosition({201, 80});
    shape7.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({22, 22});
    shape8.setRotation(0);
    shape8.setPosition({258, 22});
    shape8.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape8);

    sf::RectangleShape shape9;
    shape9.setSize({22, 22});
    shape9.setRotation(0);
    shape9.setPosition({258, 158});
    shape9.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape9);

    sf::RectangleShape shape10;
    shape10.setSize({30, 158});
    shape10.setRotation(20);
    shape10.setPosition({350, 20});
    shape10.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape10);

    sf::RectangleShape shape11;
    shape11.setSize({30, 158});
    shape11.setRotation(-20);
    shape11.setPosition({350, 30});
    shape11.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape11);

    sf::RectangleShape shape12;
    shape12.setSize({80, 30});
    shape12.setRotation(0);
    shape12.setPosition({320, 110});
    shape12.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape12);

    sf::RectangleShape shape13;
    shape13.setSize({27, 10});
    shape13.setRotation(0);
    shape13.setPosition({350, 20});
    shape13.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape13);

    sf::RectangleShape shape14;
    shape14.setSize({28, 14});
    shape14.setRotation(0);
    shape14.setPosition({296, 166});
    shape14.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape14);

    sf::RectangleShape shape15;
    shape15.setSize({28, 14});
    shape15.setRotation(0);
    shape15.setPosition({404, 166});
    shape15.setFillColor(sf::Color(0xFA, 0x80, 0x72));
    window.draw(shape15);

    window.display();

    sf::sleep(sf::seconds(5));
}