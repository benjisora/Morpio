#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

#include <iostream>

class Player
{
    public:
        Player(std::string pseudo, int id);
        virtual ~Player();
        std::string getPseudo();
        int getId();
        sf::Color getColor();

    protected:

    private:
        std::string m_pseudo;
        int m_id;
        sf::Color color;
};

#endif // PLAYER_H
