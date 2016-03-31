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
