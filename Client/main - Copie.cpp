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

    /*do
    {
        socket = new sf::TcpSocket();

        //Demande des infos de connexion

        cout << "Entrez IP : ";
        getline(cin, ip);
        cout << "Entrez port : ";
        getline(cin, portString);
        stringstream buffer(portString);
        buffer >> port;
        cout << "Entrez port : ";
        getline(cin, portString);
        stringstream buffer(portString);
        buffer >> port;

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
    while(code == 1);*/


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

    // We have to do this because we don't use SFML to draw.
    window.resetGLStates();

    // Create an SFGUI. This is required before doing anything with SFGUI.
    sfg::SFGUI sfgui;

    // Create our main SFGUI window
    auto app_window = sfg::Window::Create();
    app_window->SetTitle( "Title" );




    sfg::Table::Ptr table = sfg::Table::Create();
    auto button1 = sfg::Button::Create();
    auto label1 = sfg::Label::Create();
    auto label2 = sfg::Label::Create();
    auto label3 = sfg::Label::Create();
    auto entry1 = sfg::Entry::Create();
    auto entry2 = sfg::Entry::Create();
    auto entry3 = sfg::Entry::Create();

    label1->SetText( "Adresse :" );
    label2->SetText( "Port :" );
    label3->SetText( "Pseudo :" );
    entry1->SetRequisition( sf::Vector2f(120.f, 0.f ));
    entry1->SetMaximumLength(15);
    entry2->SetRequisition( sf::Vector2f(80.f, 0.f ));
    entry2->SetMaximumLength(5);
    entry3->SetRequisition( sf::Vector2f(80.f, 0.f ));
    button1->SetLabel( "Connexion" );
    button1->GetSignal( sfg::Widget::OnLeftClick ).Connect(std::bind(&OnButtonClick));


    table->Attach( label1, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    table->Attach( entry1, sf::Rect<sf::Uint32>( 1, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    table->Attach( label2, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    table->Attach( entry2, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    table->Attach( label3, sf::Rect<sf::Uint32>( 0, 2, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    table->Attach( entry3, sf::Rect<sf::Uint32>( 1, 2, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    table->Attach( button1, sf::Rect<sf::Uint32>( 0, 3, 2, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));

    table->SetRowSpacings( 10.f );
    table->SetColumnSpacings( 10.f );

    app_window->Add( table );

    // Start the game loop
    while ( window.isOpen() )
    {
        // Process events
        sf::Event event;

        while ( window.pollEvent( event ) )
        {
            // Handle events
            app_window->HandleEvent( event );

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

        // Update the GUI, note that you shouldn't normally
        // pass 0 seconds to the update method.
        app_window->Update( 0.f );

        window.clear();

        sfgui.Display( window );

        window.display();
    }



    delete socket;
    return EXIT_SUCCESS;
}
