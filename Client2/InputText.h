#ifndef INPUTTEXT_H
#define INPUTTEXT_H
#include <SFML/Graphics.hpp>
#include <string>

class InputText
{
    public:
        InputText();
        virtual ~InputText();
        InputText(sf::Vector2f position);
        InputText(sf::Vector2f position, std::string displayText);
        InputText(sf::Vector2f position, sf::Vector2f size);
        InputText(sf::Vector2f position, sf::Vector2f size, std::string displayText);

        void create(sf::Vector2f position);
        void create(sf::Vector2f position, std::string displayText);
        void create(sf::Vector2f position, sf::Vector2f size);
        void create(sf::Vector2f position, sf::Vector2f size, std::string displayText);


        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setText(std::string text);
        void setDisplayText(std::string displayText);
        void setOutlineColor(sf::Color color);
        void setBackgroundColor(sf::Color color);
        void setTrickness(int trickness);
        void setMaxLength(int m_maxLength);

        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        std::string getText();
        std::string getDisplayText();
        sf::Color getOutlineColor();
        sf::Color getBackgroundColor();
        int getTrickness();
        bool getSelected();

        void event(sf::Event &event);
        void step();
        void draw(sf::RenderWindow &window);


    protected:
    private:
        sf::RectangleShape m_box;
        sf::Font m_font;
        sf::Text m_boxText;
        sf::Text m_displayBoxText;
        sf::RectangleShape m_cursor;

        std::string m_text;
        std::string m_displayText;
        bool m_selected;
        bool password;
        int m_maxLength;

        sf::Vector2i localPosition;

        sf::Clock clock;
        sf::Time elapsed1;
};

#endif // INPUTTEXT_H
