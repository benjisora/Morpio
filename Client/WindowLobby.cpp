#include "WindowLobby.h"

WindowLobby::WindowLobby(sf::TcpSocket* socket)
{
    m_socket = socket;

    m_window = sfg::Window::Create();
    m_table = sfg::Table::Create();
    m_button1 = sfg::Button::Create();
    m_button2 = sfg::Button::Create();
}

WindowLobby::~WindowLobby()
{
    //dtor
}

void WindowLobby::create(sf::RenderWindow& window)
{
    m_window->SetTitle( "Lobby" );
    m_window->SetId("Window");
    sfg::Context::Get().GetEngine().SetProperty("#Window", "TitleBackgroundColor", sf::Color(50,50,50));
    m_window->SetPosition(
		sf::Vector2f(
			static_cast<float>(window.getSize().x / 2 )-105,
			static_cast<float>(window.getSize().y / 2 )-90
		)
	);


    m_button1->SetLabel( "Créer une partie" );
    m_button1->GetSignal( sfg::Button::OnLeftClick ).Connect(std::bind( &WindowLobby::onButtonClick1, this));
    m_button2->SetLabel( "Partie rapide" );
    m_button2->GetSignal( sfg::Button::OnLeftClick ).Connect(std::bind( &WindowLobby::onButtonClick2, this));

    m_table->Attach( m_button1, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->Attach( m_button2, sf::Rect<sf::Uint32>( 1, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->SetRowSpacings( 10.f );
    m_table->SetColumnSpacings( 10.f );

    m_window->Add( m_table );



    m_data << 5;
    if (m_socket->send(m_data) != sf::Socket::Done)
        cout << "Impossible d'envoyer les donnees au serveur" << std::endl;
    else
        cout << "Envoie du pseudo" << endl;

    if (m_socket->receive(m_data) != sf::Socket::Done)
            cout << "Erreur receive" << endl;
    m_data >> code;
    m_data.clear();
    cout << code << endl;
}

void WindowLobby::event(sf::Event& event)
{
    m_window->HandleEvent( event );
}

void WindowLobby::step()
{
    m_window->Update( 0.f );
}

void WindowLobby::draw(sf::RenderWindow& window)
{

}

void WindowLobby::onButtonClick1()
{


}

void WindowLobby::onButtonClick2()
{


}

void WindowLobby::show()
{
    m_window->Show(true);
    activated = true;
}

void WindowLobby::hidden()
{
    m_window->Show(false);
    activated = false;
}

bool WindowLobby::getActivated()
{
    return activated;
}
