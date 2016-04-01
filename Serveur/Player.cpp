#include "Player.h"

Player::Player(sf::TcpSocket* socket, string pseudo)
{
    m_socket = ;
    m_pseudo = pseudo;
    m_score = 0;
}

Player::~Player()
{
    //dtor
}

Player::getSocket()
{
    return m_socket;
}
