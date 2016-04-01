#include "InputText.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>



InputText::InputText()
{
    m_box.setPosition(0,0);
    m_box.setSize(sf::Vector2f(192,32));
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = "";
    m_selected = false;
    m_maxLength = -1;
}

InputText::~InputText()
{
    //dtor
}

InputText::InputText(sf::Vector2f position)
{
    m_box.setPosition(position);
    m_box.setSize(sf::Vector2f(192,32));
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = "";
    m_selected = false;
    m_maxLength = -1;
}

InputText::InputText(sf::Vector2f position, std::string displayText)
{
    m_box.setPosition(position);
    m_box.setSize(sf::Vector2f(192,32));
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = displayText;
    m_selected = false;
    m_maxLength = -1;


    if (!m_font.loadFromFile("Exo-Light.otf"))
    {
        // error...
    }
    m_displayBoxText.setFont(m_font);
    m_displayBoxText.setCharacterSize(15);
    m_displayBoxText.setColor(sf::Color(50,50,50,100));
    m_displayBoxText.setPosition(m_box.getPosition().x+10,m_box.getPosition().y+6);
    m_displayBoxText.setString(m_displayText);

    m_boxText.setFont(m_font);
    m_boxText.setCharacterSize(15);
    m_boxText.setColor(sf::Color(50,50,50,255));
    m_boxText.setPosition(m_box.getPosition().x+10,m_box.getPosition().y+6);

    m_cursor.setSize(sf::Vector2f(1,m_boxText.getCharacterSize()*1.3));
    m_cursor.setFillColor(sf::Color(50,50,50));
}

InputText::InputText(sf::Vector2f position, sf::Vector2f size)
{
    m_box.setPosition(position);
    m_box.setSize(size);
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = "";
    m_selected = false;
    m_maxLength = -1;
}

InputText::InputText(sf::Vector2f position, sf::Vector2f size, std::string displayText)
{
    m_box.setPosition(position);
    m_box.setSize(size);
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = displayText;
    m_selected = false;
    m_maxLength = -1;
}





void InputText::create(sf::Vector2f position)
{
    m_box.setPosition(position);
    m_box.setSize(sf::Vector2f(192,32));
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = "";
    m_selected = false;
    m_maxLength = -1;
}

void InputText::create(sf::Vector2f position, std::string displayText)
{
    m_box.setPosition(position);
    m_box.setSize(sf::Vector2f(192,32));
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = displayText;
    m_selected = false;
    m_maxLength = -1;


    if (!m_font.loadFromFile("Exo-Light.otf"))
    {
        // error...
    }
    m_displayBoxText.setFont(m_font);
    m_displayBoxText.setCharacterSize(15);
    m_displayBoxText.setColor(sf::Color(50,50,50,100));
    m_displayBoxText.setPosition(m_box.getPosition().x+10,m_box.getPosition().y+6);
    m_displayBoxText.setString(m_displayText);

    m_boxText.setFont(m_font);
    m_boxText.setCharacterSize(15);
    m_boxText.setColor(sf::Color(50,50,50,255));
    m_boxText.setPosition(m_box.getPosition().x+10,m_box.getPosition().y+6);

    m_cursor.setSize(sf::Vector2f(1,m_boxText.getCharacterSize()*1.3));
    m_cursor.setFillColor(sf::Color(50,50,50));
}

void InputText::create(sf::Vector2f position, sf::Vector2f size)
{
    m_box.setPosition(position);
    m_box.setSize(size);
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = "";
    m_selected = false;
    m_maxLength = -1;
}

void InputText::create(sf::Vector2f position, sf::Vector2f size, std::string displayText)
{
    m_box.setPosition(position);
    m_box.setSize(size);
    m_box.setOutlineColor(sf::Color(0,0,0));
    m_box.setFillColor(sf::Color(255,255,255));
    m_box.setOutlineThickness(1);
    m_text = "";
    m_displayText = displayText;
    m_selected = false;
    m_maxLength = -1;
}

void InputText::setPosition(sf::Vector2f position)
{
    m_box.setPosition(position);
}

void InputText::setSize(sf::Vector2f size)
{
    m_box.setSize(size);
}

void InputText::setText(std::string text)
{
    m_text = text;
    m_selected = true;
}

void InputText::setDisplayText(std::string displayText)
{
    m_displayText = displayText;
}

void InputText::setOutlineColor(sf::Color color)
{
    m_box.setOutlineColor(color);
}

void InputText::setBackgroundColor(sf::Color color)
{
     m_box.setFillColor(color);
}

void InputText::setTrickness(int trickness)
{
    m_box.setOutlineThickness(trickness);
}

void InputText::setMaxLength(int maxLength)
{
    m_maxLength = maxLength;
}

sf::Vector2f InputText::getPosition()
{
    return m_box.getPosition();
}

sf::Vector2f InputText::getSize()
{
    return m_box.getSize();
}

std::string InputText::getText()
{
    return m_text;
}

std::string InputText::getDisplayText()
{
    return m_displayText;
}

sf::Color InputText::getOutlineColor()
{
    return m_box.getOutlineColor();
}

sf::Color InputText::getBackgroundColor()
{
    return m_box.getFillColor();
}

int InputText::getTrickness()
{
    return m_box.getOutlineThickness();
}

bool InputText::getSelected()
{
    return m_selected;
}

void InputText::event(sf::Event &event)
{
    if (m_selected == true && event.type == sf::Event::TextEntered)
    {
        if(event.text.unicode == '\b' && m_text.size()==0)
            m_text == "";
        else if (event.text.unicode == '\b' && m_text.size()>0)
            m_text.erase(m_text.size()-1, 1);
        else if(m_maxLength == -1)
            m_text+=event.text.unicode;
        else if(m_maxLength > 0)
            if(m_text.size() < m_maxLength)
                m_text+=event.text.unicode;


    }
}

void InputText::step()
{
    if(localPosition.x >= m_box.getPosition().x && localPosition.x <= m_box.getPosition().x+m_box.getSize().x
            && localPosition.y >=  m_box.getPosition().y && localPosition.y <= m_box.getPosition().y+m_box.getSize().y)
    {
        SetCursor(LoadCursor(NULL, IDC_IBEAM));
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(localPosition.x >= m_box.getPosition().x && localPosition.x <= m_box.getPosition().x+m_box.getSize().x
            && localPosition.y >=  m_box.getPosition().y && localPosition.y <= m_box.getPosition().y+m_box.getSize().y)
            m_selected = true;
        else
            m_selected = false;
    }

    if(m_selected == true)
    {
        m_displayBoxText.setString("");
        m_cursor.setPosition(sf::Vector2f(m_boxText.getPosition().x+m_boxText.getLocalBounds().width, m_boxText.getPosition().y));
        m_boxText.setString(m_text);
    }
    else
    {
         m_displayBoxText.setString(m_displayText);
    }

    elapsed1 = clock.getElapsedTime();

    if(elapsed1.asMilliseconds() > 1000)
        clock.restart();
}

void InputText::draw(sf::RenderWindow& window)
{
    localPosition = sf::Mouse::getPosition(window);

    window.draw(m_box);
    if(m_text.size() == 0)
        window.draw(m_displayBoxText);
    window.draw(m_boxText);
    if(m_selected == true && elapsed1.asMilliseconds() > 500)
        window.draw(m_cursor);

}



