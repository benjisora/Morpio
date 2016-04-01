#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <string>

using namespace std;

class Player
{
    public:
        Player(sf::TcpSocket* socket, string pseudo);
        virtual ~Player();
        sf::TcpSocket getSocket();

    protected:

    private:
        sf::TcpSocket* m_socket;
        string m_pseudo;
        int m_score;
};

#endif // PLAYER_H
