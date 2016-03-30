#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "LoginWindow.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void create();
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);

    protected:

    private:
    std::vector<Player> m_player;
    std::vector<int> m_tab;
    Board m_board;
    LoginWindow m_loginWindow;

};

#endif // GAME_H
