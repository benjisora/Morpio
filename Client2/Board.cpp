#include "Board.h"

Board::Board()
{

}

Board::~Board()
{
    //dtor
}

void Board::create(int size)
{
    m_size = size;
    float sizeRect = (768/m_size)-5;

    for(int y=0; y<m_size; y++)
    {
        for(int x=0; x<m_size; x++)
        {
            sf::RectangleShape rect;
            rect.setFillColor(sf::Color(60,60,60));
            rect.setSize(sf::Vector2f(sizeRect, sizeRect));
            rect.setPosition(sf::Vector2f(x*(sizeRect+5)+5, y*(sizeRect+5)+5));
            m_tab.push_back(rect);
        }
    }
}

void Board::step()
{

}

void Board::draw(sf::RenderWindow& window)
{

    for(int y=0; y<m_size; y++)
    {
        for(int x=0; x<m_size; x++)
        {
            window.draw(m_tab[x+m_size*y]);
        }
    }
}

void Board::setColor(int x, int y, sf::Color color)
{
    m_tab[x+m_size*y].setFillColor(color);
}
