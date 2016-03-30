#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button();
        virtual ~Button();
        void create(sf::Vector2f position, sf::Vector2f size);
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);


    protected:

    private:
        sf::RectangleShape m_rect1, m_rect2;

        std::string m_text;
        sf::Font m_font;
        sf::Text m_boxText;

        sf::Vector2i localPosition;
};

#endif // BUTTON_H
