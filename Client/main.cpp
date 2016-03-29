#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <random>
#include <thread>
#include <sstream>
#include "WindowLogIn.h"
#include "WindowLobby.h"

using namespace std;

int main()
{
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "SFGUI Box Example", sf::Style::Titlebar | sf::Style::Close );
    window.resetGLStates();

    /****************************
    CREATE
    *****************************/

    sfg::SFGUI sfgui;

    sf::TcpSocket* socket;
    sf::Packet data;



    cout << "Client start" << endl;



    WindowLogIn windowLogIn(socket);
    windowLogIn.create(window);

    WindowLobby windowLobby(socket);
    windowLobby.create(window);
    windowLobby.hidden();

    while ( window.isOpen() )
    {
        sf::Event event;

        while ( window.pollEvent( event ) )
        {
            windowLogIn.event(event);
            windowLobby.event(event);


            if ( event.type == sf::Event::Closed )
            {
                window.close();
            }
            if(event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        /****************************
        STEP
        *****************************/

        if(windowLogIn.getConnected() == false)
        {
            windowLogIn.step();
        }
        else
        {
            windowLogIn.hidden();
            windowLobby.show();
            windowLobby.step();
        }


        window.clear(sf::Color(100,100,100));

        /****************************
        DRAW
        *****************************/

        sfgui.Display( window );

        window.display();
    }



    delete socket;
    return EXIT_SUCCESS;
}
