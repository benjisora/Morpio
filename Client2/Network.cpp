#include "Network.h"


/*sf::Packet& operator <<(sf::Packet& packet, const Player& player)
{
    return packet << player.getPseudo() << player.getId() << player.getColor();
}

sf::Packet& operator >>(sf::Packet& packet, Player& player)
{
    return packet  >> player.getPseudo() >> player.getId() >> player.getColor();
}*/


Network::Network()
{

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
    {
         m_data >> code;
        std::cout << "code -> " << code << std::endl;
    }
    m_data.clear();


    return code;
}

int Network::receiveSize()
{
    int size = -1;
    if (m_socket.receive(m_data) == sf::Socket::Done)
    {
         m_data >> size;
        std::cout << "size -> " << size << std::endl;
    }
    m_data.clear();


    return size;
}

int Network::receiveErrorCreate()
{
    int error = -1;
    if (m_socket.receive(m_data) == sf::Socket::Done)
    {
         m_data >> error;
        std::cout << "error -> " << error << std::endl;
    }
    m_data.clear();


    return error;
}

/*std::vector<std::string> Network::receivePlayerName()
{
    std::vector<std::string> p;
    if (m_socket.receive(m_data) == sf::Socket::Done)
         m_data >> p;
    m_data.clear();
    return p;
}*/




void Network::setBlocking(bool block)
{
     m_socket.setBlocking(block);
}

