#include "Button.h"

Button::Button()
{
    //ctor
}

Button::~Button()
{
    //dtor
}

void Button::create(sf::Vector2f position, sf::Vector2f size, std::string label)
{
    if (!m_font.loadFromFile("res/Exo-Bold.otf"))
    {
        //std::cout << "error font" << std::endl;
    }

    m_boxText.setFont(m_font);
    m_boxText.setCharacterSize(22.5);
    m_boxText.setColor(sf::Color(255,255,255,255));
    m_boxText.setString(label);
    //m_boxText.setOrigin(m_boxText.getLocalBounds().width/2, m_boxText.getLocalBounds().height/2);
    m_boxText.setPosition(position.x+m_boxText.getGlobalBounds().width/2.5, position.y+m_boxText.getGlobalBounds().height/2);

    m_rect1.setPosition(position.x, position.y);
    m_rect1.setSize(sf::Vector2f(size.x,size.y));
    m_rect1.setFillColor(sf::Color(200,70,70));

    m_rect2.setPosition(position.x, position.y+size.y-4);
    m_rect2.setSize(sf::Vector2f(size.x, 4));
    m_rect2.setFillColor(sf::Color(170,50,50));

    m_clicked = false;

}

void Button::event(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased)
    {
        mouseOnButton = (localPosition.x >= m_rect1.getPosition().x && localPosition.x <= m_rect1.getPosition().x+m_rect1.getSize().x
        && localPosition.y >=  m_rect1.getPosition().y && localPosition.y <= m_rect1.getPosition().y+m_rect1.getSize().y);

        if (event.key.code == sf::Mouse::Left && mouseOnButton)
        {
            m_clicked = true;
        }
    }
}

void Button::step()
{

    mouseOnButton = (localPosition.x >= m_rect1.getPosition().x && localPosition.x <= m_rect1.getPosition().x+m_rect1.getSize().x
        && localPosition.y >=  m_rect1.getPosition().y && localPosition.y <= m_rect1.getPosition().y+m_rect1.getSize().y);

    if (mouseOnButton)
        m_rect1.setFillColor(sf::Color(230,70,70));
    else
        m_rect1.setFillColor(sf::Color(200,70,70));

    m_clicked = false;
}

void Button::draw(sf::RenderWindow& window)
{
    localPosition = sf::Mouse::getPosition(window);

    window.draw(m_rect1);
    window.draw(m_rect2);
    window.draw(m_boxText);
}

bool Button::isClicked()
{
    return m_clicked;
}
