#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Morpio", sf::Style::Default, settings);

    Game game;
    game.create();

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            game.event(event);
        }
        game.step();
        window.clear(sf::Color(50,50,50));
        game.draw(window);
        window.display();
    }

    return 0;
}
