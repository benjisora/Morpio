#include "Player.h"

Player::Player(std::string pseudo, int id)
{
    m_pseudo = pseudo;
    m_id = id;


    switch(id)
    {
    case(1):
        color = sf::Color(52, 152, 219); //bleu
        break;
    case(2):
        color = sf::Color(231, 76, 60); //rouge
        break;
    case(3):
        color = sf::Color(39, 174, 96); //vert
        break;
    case(4):
        color = sf::Color(142, 68, 172); //violet
        break;
    case(5):
        color = sf::Color(241, 196, 15); //jaune
        break;
    case(6):
        color = sf::Color(244, 124, 195); //rose
        break;

    }

}

Player::~Player()
{
    //dtor
}

std::string Player::getPseudo()
{
    return m_pseudo;
}

int Player::getId()
{
    return m_id;
}

void Player::setId(int id)
{
    m_id = id;
}

sf::Color Player::getColor()
{
    return color;
}
