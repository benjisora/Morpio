#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::create()
{
    m_board.create(5);
    m_board.setColor(1, 1, sf::Color(100, 150, 150));

    m_loginWindow.create();
    m_gameCreateWindows.create();

    m_phase = 1;
}

void Game::event(sf::Event& event)
{
    if(m_phase == 1)
    {
        m_loginWindow.event(event);
    }

    if(m_phase == 2)
    {
        m_gameCreateWindows.event(event);
    }
}

void Game::step()
{
    if(m_phase == 1)
    {
        if(m_loginWindow.isClicked())
        {
            std::cout << m_loginWindow.getIp() << "   " << m_loginWindow.getPort() << "   " << m_loginWindow.getPseudo() << std::endl;
            if(network.connect(m_loginWindow.getIp(), m_loginWindow.getPort(), m_loginWindow.getPseudo()))
            {
                m_phase = 2;
            }
            else
            {
                std::cout << "Erreur connect" << std::endl;
            }
        }
        m_board.step();
        m_loginWindow.step();
    }

    if(m_phase == 2)
    {
        m_board.step();
        m_gameCreateWindows.step();
    }


}

void Game::draw(sf::RenderWindow& window)
{
    if(m_phase == 1)
    {
        m_board.draw(window);
        m_loginWindow.draw(window);
    }

    if(m_phase == 2)
    {
        m_board.draw(window);
        m_gameCreateWindows.draw(window);
    }
}
