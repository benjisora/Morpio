#include "Button.h"

Button::Button()
{
    //ctor
}

Button::~Button()
{
    //dtor
}

void Button::create(sf::Vector2f position, sf::Vector2f size)
{
    if (!m_font.loadFromFile("Exo-Bold.otf"))
    {
        //std::cout << "error font" << std::endl;
    }

    m_boxText.setFont(m_font);
    m_boxText.setCharacterSize(22.5);
    m_boxText.setColor(sf::Color(255,255,255,255));
    m_boxText.setString("Connexion");
    m_boxText.setPosition(position.x+m_boxText.getGlobalBounds().width/2.5, position.y+m_boxText.getGlobalBounds().height/2);

    m_rect1.setPosition(position.x, position.y);
    m_rect1.setSize(sf::Vector2f(size.x,size.y));
    m_rect1.setFillColor(sf::Color(200,70,70));

    m_rect2.setPosition(position.x, position.y+size.y-4);
    m_rect2.setSize(sf::Vector2f(size.x, 4));
    m_rect2.setFillColor(sf::Color(170,50,50));


}

void Button::event(sf::Event& event)
{

}

void Button::step()
{

    if(localPosition.x >= m_rect1.getPosition().x && localPosition.x <= m_rect1.getPosition().x+m_rect1.getSize().x
        && localPosition.y >=  m_rect1.getPosition().y && localPosition.y <= m_rect1.getPosition().y+m_rect1.getSize().y)
        m_rect1.setFillColor(sf::Color(230,70,70));
    else
        m_rect1.setFillColor(sf::Color(200,70,70));

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
         if(localPosition.x >= m_rect1.getPosition().x && localPosition.x <= m_rect1.getPosition().x+m_rect1.getSize().x
        && localPosition.y >=  m_rect1.getPosition().y && localPosition.y <= m_rect1.getPosition().y+m_rect1.getSize().y)
        {
             //m_rect1.setFillColor(sf::Color(170,30,30));
        }
        else
        {
            //m_rect1.setFillColor(sf::Color(200,70,70));

        }

    }
}

void Button::draw(sf::RenderWindow& window)
{
    localPosition = sf::Mouse::getPosition(window);

    window.draw(m_rect1);
    window.draw(m_rect2);
    window.draw(m_boxText);
}
