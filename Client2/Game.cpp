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
    //m_board.setColor(1, 1, sf::Color(100, 150, 150));

    m_loginWindow.create();
    m_gameCreateWindows.create();

    wait.create();

    m_phase = 3;

    /*Player p1("Joueur 1", 0);
    m_player.push_back(p1);
    Player p2("Joueur 2", 1);
    m_player.push_back(p2);
    Player p3("Joueur 3", 2);
    m_player.push_back(p3);
    Player p4("Joueur 4", 3);
    m_player.push_back(p4);
    Player p5("Joueur 5", 4);
    m_player.push_back(p5);
    Player p6("Joueur 6", 5);
    m_player.push_back(p6);*/



    //std::cin >> m_phase;

    gameCreated = false;
    playerTurn = 0;
}

void Game::event(sf::Event& event)
{
    /*if (event.type == sf::Event::Closed)
        network.sendCode(12);*/


    if(m_phase == 1)
    {
        m_loginWindow.event(event);
    }

    if(m_phase == 2)
    {
        m_gameCreateWindows.event(event);
    }

    if(m_phase == 4)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.key.code == sf::Mouse::Left &&
                localPosition.x >= 0 && localPosition.x <= 768
                && localPosition.y >=  0 && localPosition.y <= 768)
            {
                posX = localPosition.x/m_board.getSizeCase();
                posY = localPosition.y/m_board.getSizeCase();

                if(idClient == playerTurn%m_player.size() && network.sendPositionClick(posX, posY)==false)
                {
                    std::cout << "error send position" << std::endl;
                }
            }
        }
    }
}

void Game::step()
{
    if(m_phase == 1)
    {
        if(m_loginWindow.isClicked())
        {
            network.setBlocking(true);
            if(network.connect(m_loginWindow.getIp(), m_loginWindow.getPort(), m_loginWindow.getPseudo()))
            {
                if(network.receiveCode()==101)
                    m_phase = 2;
                else
                    m_phase = 3;

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
        if(m_gameCreateWindows.isClicked())
        {
            if(network.sendCreateGame(m_gameCreateWindows.getNbPlayer(), m_gameCreateWindows.getSizeGrid(), m_gameCreateWindows.getScoreMin()))
            {
                network.setBlocking(true);
                int error = network.receiveCode();
                if(error == 0)
                {
                    m_phase = 3;
                }
                else if(error == 1)
                {
                    std::cout << "Error dans les champs" << std::endl;
                }
                else
                {
                    std::cout << "Error" << std::endl;
                }

            }
            else
            {
                std::cout << "Erreur connect" << std::endl;
            }
        }
        m_board.step();
        m_gameCreateWindows.step();
    }
    if(m_phase == 3)
    {
        wait.step();

        network.setBlocking(false);
        code = network.receiveCode();

        if(code==5)
        {
            m_phase = 4;
        }
        else if(code==101)
        {
            m_phase = 2;
        }


    }
    if(m_phase == 4)
    {


        if(/*size>0 && */gameCreated == false)
        {
            network.setBlocking(true);
            int size = network.receiveSize();
            network.setBlocking(false);
            m_board.create(size);

            for(int i=0; i<size*size; i++)
                m_tab.push_back(0);


            int id;
            std::string pseudo;
            int code2;
            int ii=1;
            do
            {
                network.setBlocking(true);
                code = network.receivePlayerName(id, pseudo);
                std::cout << "id : " << ii << "     pseudo : " << pseudo << std::endl;
                if(pseudo != "")
                {
                    Player p1(pseudo, ii);
                    m_player.push_back(p1);

                    if(pseudo == m_loginWindow.getPseudo())
                    {
                        idClient = ii-1;
                    }
                    ii++;
                }
            }
            while(code !=8);


            network.setBlocking(false);
            m_inGameWindow.create(m_player);
            code = 0;

            gameCreated = true;
        }


        network.setBlocking(false);
        code = network.receivePosition(posX, posY);
        if(code == 11)
        {
            m_board.setColor(posX, posY, m_player[playerTurn%m_player.size()].getColor());
            playerTurn++;
            code = 0;
            m_inGameWindow.setCurrentPlayer(playerTurn%m_player.size());
        }
        else
        {
            posX = 0;
            posY = 0;
        }

        m_board.step();
        m_inGameWindow.step();
    }
}

void Game::draw(sf::RenderWindow& window)
{
    localPosition = sf::Mouse::getPosition(window);

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

    if(m_phase == 3)
    {
        wait.draw(window);
    }
    if(m_phase == 4)
    {
        m_board.draw(window);
        m_inGameWindow.draw(window);
    }
}
