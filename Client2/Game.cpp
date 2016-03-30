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
}

void Game::event(sf::Event& event)
{
    m_loginWindow.event(event);
}

void Game::step()
{
    m_board.step();
    m_loginWindow.step();
}

void Game::draw(sf::RenderWindow& window)
{
    m_board.draw(window);
    m_loginWindow.draw(window);
}
