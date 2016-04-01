#include "InGameWindow.h"

InGameWindow::InGameWindow()
{
    //ctor
}

InGameWindow::~InGameWindow()
{
    //dtor
}

void InGameWindow::create(std::vector<Player> player)
{
    if (!font.loadFromFile("Exo-Regular.otf"))
    {
        std::cout << "Error font: can't find \"Exo-Regular.otf\"." << std::endl;
    }
    if (!font2.loadFromFile("Exo-Light.otf"))
    {
        std::cout << "Error font: can't find \"Exo-Light.otf\"." << std::endl;
    }

    for(int i=0; i<player.size(); i++)
    {
        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(20);
        t.setColor(sf::Color(255,255,255,255));
        t.setPosition(840,40+i*50);
        t.setString(player[i].getPseudo());
        m_text.push_back(t);


        sf::RectangleShape r1;
        r1.setSize(sf::Vector2f(170,2));
        r1.setFillColor(sf::Color(70,70,70));
        r1.setPosition(830,68+i*50);
        m_separator.push_back(r1);

        sf::RectangleShape r2;
        r2.setSize(sf::Vector2f(30,30));
        r2.setFillColor(player[i].getColor());
        r2.setPosition(785,40+i*50);
        m_rect.push_back(r2);
    }

    m_currentRectangle.setSize(sf::Vector2f(0,30));
    m_currentRectangle.setFillColor(sf::Color(70,70,70));
    m_currentRectangle.setPosition(830, 40);

    currentPlayer = 0;
    animation = true;
    a=0;
}

void InGameWindow::event()
{

}

void InGameWindow::step()
{
    if(animation == true)
    {
        a++;
        v = a / 60;
        v = SMOOTHSTEP(v)*SMOOTHSTEP(v);
        X = (170 * v) + (0 * (1 - v));
        if(a == 60)
        {
            animation = false;
            a=0;

        }

        m_currentRectangle.setSize(sf::Vector2f(X, 30));
    }

}

void InGameWindow::draw(sf::RenderWindow& window)
{
    window.draw(m_currentRectangle);
    for(int i=0; i<m_text.size(); i++)
    {
        window.draw(m_rect[i]);
        window.draw(m_separator[i]);
        window.draw(m_text[i]);
    }
}

void InGameWindow::setCurrentPlayer(int id)
{
    m_currentRectangle.setPosition(830, 40+id*50);
    animation = true;
}
