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
    {
        m_data.clear();
        return false;
    }

    return true;
}

bool Network::sendCreateGame(int nbPlayer, int sizeGrid, int scoreMin)
{
    m_data << 0 << nbPlayer << sizeGrid << scoreMin;
    if (m_socket.send(m_data) != sf::Socket::Done)
    {
        m_data.clear();
        return false;
    }

    return true;
}

bool Network::sendPositionClick(int posX, int posY)
{
    m_data << posX << posY;
    if (m_socket.send(m_data) != sf::Socket::Done)
    {
        m_data.clear();
        return false;
    }
    std::cout << "send xy    >> " << posX << " " << posY << std::endl;
    m_data.clear();

    return true;
}

bool Network::sendCode(int code)
{
    m_data << code << -1 << -1;
    if (m_socket.send(m_data) != sf::Socket::Done)
    {
        m_data.clear();
        return false;
    }
    std::cout << "send >> " << code << std::endl;
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

int Network::receivePlayerName(int& id, std::string& pseudo)
{
    int code = -1;
    if (m_socket.receive(m_data) == sf::Socket::Done)
         m_data >> code >> id >> pseudo;
    m_data.clear();
    return code;
}


int Network::receivePlayerTurn(int& idPlayerTurn)
{
    int code = -1;
    if (m_socket.receive(m_data) == sf::Socket::Done)
    {
         m_data >> code >> idPlayerTurn;
        std::cout << "id turn -> " << idPlayerTurn << std::endl;
    }
    m_data.clear();


    return code;
}

int Network::receivePosition(int& posX, int& posY)
{
    int code = -1;
    if (m_socket.receive(m_data) == sf::Socket::Done)
    {
         m_data >> code >> posX >> posY;
        std::cout << "receive xy << " << posX << " " << posY << std::endl;
    }
    m_data.clear();


    return code;
}

int Network::receiveWinner(int& id)
{
    int code = -1;
    if (m_socket.receive(m_data) == sf::Socket::Done)
         m_data >> code >> id;
    m_data.clear();
    return code;
}


void Network::setBlocking(bool block)
{
     m_socket.setBlocking(block);
}

