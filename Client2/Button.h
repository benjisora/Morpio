#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "Network.h"
#include "signal.h"
#include <cstdio>
#include <iostream>

class Button
{
    public:
        Button();
        virtual ~Button();
        void create(sf::Vector2f position, sf::Vector2f size, std::string label);
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);
        bool isClicked();

    protected:

    private:
        sf::RectangleShape m_rect1, m_rect2;

        bool m_clicked;

        bool mouseOnButton;

        std::string m_text;
        sf::Font m_font;
        sf::Text m_boxText;

        sf::Vector2i localPosition;
};

#endif // BUTTON_H
