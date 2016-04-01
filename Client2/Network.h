#ifndef NETWORK_H
#define NETWORK_H
#include <iostream>
#include <SFML/Network.hpp>

class Network
{
    public:
        Network();
        virtual ~Network();
        bool connect(std::string ip, int port, std::string pseudo);
        bool sendCreateGame(int nbPlayer, int sizeGrid, int scoreMin);
        bool sendPositionClick(int posX, int posY);

        int receiveCode();

    protected:

    private:
        sf::TcpSocket m_socket;
        sf::Packet m_data;
        int m_code=-1;
};

#endif // NETWORK_H
