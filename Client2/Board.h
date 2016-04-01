#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

class Board
{
    public:
        Board();
        virtual ~Board();
        void create(int size);
        void step();
        void draw(sf::RenderWindow& window);
        void setColor(int x, int y, sf::Color color);
        int getSizeCase();

    protected:

    private:
        std::vector<sf::RectangleShape> m_tab;
        int m_size;

};

#endif // BOARD_H
