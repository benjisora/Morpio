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
    m_resultWindow.create();

    wait.create();

    m_phase = 1;


    //std::cin >> m_phase;

    gameCreated = false;
    playerTurn = 0;
}

void Game::event(sf::Event& event)
{
    /*if (event.type == sf::Event::Closed)
        network.sendCode(14);*/


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
    if(m_phase == 5)
    {
        m_resultWindow.event(event);
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
        m_resultWindow.setTextToast("");
        int id;
        int code2, code3;
        if(gameCreated == false)
        {
            playerTurn = 0;
            network.setBlocking(true);
            int size = network.receiveSize();
            network.setBlocking(false);
            m_board.create(size);

            for(int i=0; i<size*size; i++)
                m_tab.push_back(0);



            std::string pseudo;

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
        code2 = network.receiveWinner(id);
        if(code == 11)
        {
            m_board.setColor(posX, posY, m_player[playerTurn%m_player.size()].getColor());
            playerTurn++;
            code = 0;
            m_inGameWindow.setCurrentPlayer(playerTurn%m_player.size());
        }
        else if(code==14)
        {
            std::cout << "An player leave" << std::endl;
            m_phase = 3;
            code  = 0;
        }
        else
        {
            posX = 0;
            posY = 0;
        }

        if(code2==13)
        {
            m_resultWindow.setText("GAGNANT : " + m_player[id+m_player[0].getId()-1].getPseudo());
            m_phase = 5;
            code2=0;
        }
        else if(code2==15)
        {
            m_resultWindow.setText("EGALITE");
            m_phase = 5;
            code2=0;
        }



        m_board.step();
        m_inGameWindow.step();
    }

    if(m_phase == 5)
    {
        if(m_resultWindow.isClickedRetry())
        {
            network.sendCode(17);
        }

        code = network.receiveCode();
        if(code==18)
        {
            m_resultWindow.setTextToast("Des clients veulent rejouer");
        }
        else if(code==16)
        {
            m_phase = 4;
            gameCreated = false;
            m_player.clear();

        }

        m_resultWindow.step();
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
    if(m_phase == 5)
    {
        m_resultWindow.draw(window);
    }
}
