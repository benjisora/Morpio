#include "Player.h"

Player::Player(std::string pseudo, int id)
{
    m_pseudo = pseudo;
    m_id = id;
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
