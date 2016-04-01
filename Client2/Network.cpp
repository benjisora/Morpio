#include "Network.h"


Network::Network()
{
    //ctor
}

Network::~Network()
{
    //dtor
}

bool Network::connect(std::string ip, int port, std::string pseudo)
{
    sf::Socket::Status status = m_socket.connect(ip, port);
    if (status != sf::Socket::Done)
        return false;

    m_data << 0 << pseudo;
    if (m_socket.send(m_data) != sf::Socket::Done)
        return false;
    m_data.clear();

    return true;
}

bool Network::sendCreateGame(int nbPlayer, int sizeGrid, int scoreMin)
{
    m_data << 0 << nbPlayer << sizeGrid << scoreMin;
    if (m_socket.send(m_data) != sf::Socket::Done)
        return false;
    m_data.clear();

    return true;
}

bool Network::sendPositionClick(int posX, int posY)
{
    m_data << 0 << posX << posY;
    if (m_socket.send(m_data) != sf::Socket::Done)
        return false;
    m_data.clear();

    return true;
}

int Network::receiveCode()
{
    int code = -1;
    if (m_socket.receive(m_data) == sf::Socket::Done)
         m_data >> code;
    m_data.clear();
    return code;
}


