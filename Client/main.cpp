#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <random>
#include <thread>
#include <sstream>

using namespace std;

bool buttonClick = false;

void OnButtonClick(bool e1)
{
    buttonClick = true;
}

int main()
{
    sf::TcpSocket* socket;
    string ip = "172.31.247.41";
    string portString = "";
    string pseudo ="";
    int port = 80;
    int code=-1;
    int idCLient=-1;
    sf::Packet data;
    string sizeGridString = "";
    int sizeGrid = -1;
    string nbPionString = "";
    int nbPion = -1;
    string ipPlayerString = "127.0.0.1";

    /****************************
    CREATE
    *****************************/

    cout << "Client start" << endl;

    do
    {
        socket = new sf::TcpSocket();

        //Demande des infos de connexion

        /*cout << "Entrez IP : ";
        getline(cin, ip);
        cout << "Entrez port : ";
        getline(cin, portString);
        stringstream buffer(portString);
        buffer >> port;
        cout << "Entrez port : ";
        getline(cin, portString);
        stringstream buffer(portString);
        buffer >> port;*/

        cout << "Entrez Pseudo : ";
        getline(cin, pseudo);

        sf::Socket::Status status = socket->connect(ip, port);
        if (status != sf::Socket::Done)
            cout << "Impossible de se connecter" << endl;
        else
            cout << "connexion etablie avec le serveur distant" << endl;
        //Envoie du pseudo
        data << 0 << pseudo;
        if (socket->send(data) != sf::Socket::Done)
            cout << "Impossible d'envoyer les donnees au serveur" << std::endl;
        else
            cout << "Envoie du pseudo" << endl;

        data.clear();
        if (socket->receive(data) != sf::Socket::Done)
            cout << "Erreur receive" << endl;
        data >> code;
        data.clear();

        if(code == 1)
        {
            delete socket;
            cout << "Le pseudo est deja utilise" << endl;
        }
    }
    while(code == 1);


    if(code==101)
    {
        idCLient = code-100;
        cout << "Vous etes les createurs de la partie." << endl;
        cout << "Veuillez renseigner les options suivantes : " << endl;
        cout << "Entrez taille de la grille : ";
        getline(cin, sizeGridString);
        stringstream buffer1(sizeGridString);
        buffer1 >> sizeGrid;
        cout << "Entrez nombre de pions a aligner : ";
        getline(cin, nbPionString);
        stringstream buffer2(nbPionString);
        buffer2 >> nbPion;

        data << 0 << sizeGrid << ipPlayerString << nbPion;
        if (socket->send(data) != sf::Socket::Done)
            std::cout << "Impossible d'envoyer les donnees au serveur" << std::endl;
        data.clear();
    }
    else if(code>101 && code<110)
    {
        idCLient = code-100;
        cout << "...En attente d'adversaire..." << endl;
    }




    /*if (socket->receive(data) != sf::Socket::Done)
       cout << "Erreur receive" << endl;
    data >> code;*/
    data.clear();


    //if(code == )
    // Create the main SFML window
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "SFGUI Box Example", sf::Style::Titlebar | sf::Style::Close );
    window.resetGLStates();




    // Start the game loop
    while ( window.isOpen() )
    {
        // Process events
        sf::Event event;

        while ( window.pollEvent( event ) )
        {
            // Close window : exit
            if ( event.type == sf::Event::Closed )
            {
                window.close();
            }
            if(event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }


        window.clear();


        window.display();
    }



    delete socket;
    return EXIT_SUCCESS;
}
