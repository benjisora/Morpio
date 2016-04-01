#ifndef INGAMEWINDOW_H
#define INGAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))

class InGameWindow
{
    public:
        InGameWindow();
        virtual ~InGameWindow();
        void create(std::vector<Player> player);
        void event();
        void step();
        void draw(sf::RenderWindow& window);
        void setCurrentPlayer(int id);

    protected:

    private:
        sf::Font font, font2;
        std::vector<sf::Text> m_text;
        std::vector<sf::RectangleShape> m_rect;
        std::vector<sf::RectangleShape> m_separator;
        int currentPlayer;
        sf::RectangleShape m_currentRectangle;
        float a;
        float v, X;
        bool animation;
};

#endif // INGAMEWINDOW_H
