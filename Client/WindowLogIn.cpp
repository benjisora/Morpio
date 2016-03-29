#include "WindowLogIn.h"
#include <sstream>

WindowLogIn::WindowLogIn(sf::TcpSocket* socket)
{
    m_socket = socket;

    m_window = sfg::Window::Create();
    m_table = sfg::Table::Create();
    m_button1 = sfg::Button::Create();
    m_label1 = sfg::Label::Create();
    m_label2 = sfg::Label::Create();
    m_label3 = sfg::Label::Create();
    m_entry1 = sfg::Entry::Create();
    m_entry2 = sfg::Entry::Create();
    m_entry3 = sfg::Entry::Create();
}

WindowLogIn::~WindowLogIn()
{
    //dtor
}

void WindowLogIn::create(sf::RenderWindow& window)
{
    m_window->SetTitle( "Connexion" );
    m_window->SetId("Window");


    sfg::Context::Get().GetEngine().SetProperty("#Window", "TitleBackgroundColor", sf::Color(50,50,50));
    m_window->SetPosition(
		sf::Vector2f(
			static_cast<float>(window.getSize().x / 2 )-105,
			static_cast<float>(window.getSize().y / 2 )-90
		)
	);

    m_label1->SetText( "Adresse :" );
    m_label2->SetText( "Port :" );
    m_label3->SetText( "Pseudo :" );
    m_entry1->SetRequisition( sf::Vector2f(120.f, 0.f ));
    m_entry1->SetMaximumLength(15);
    m_entry1->SetText("172.31.247.41");
    m_entry2->SetRequisition( sf::Vector2f(80.f, 0.f ));
    m_entry2->SetMaximumLength(5);
    m_entry2->SetText("80");
    m_entry3->SetRequisition( sf::Vector2f(80.f, 0.f ));
    m_entry3->SetId("Pseudo");
    m_button1->SetLabel( "Connexion" );
    m_button1->GetSignal( sfg::Button::OnLeftClick ).Connect(std::bind( &WindowLogIn::onButtonClick, this));

    m_table->Attach( m_label1, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->Attach( m_entry1, sf::Rect<sf::Uint32>( 1, 0, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->Attach( m_label2, sf::Rect<sf::Uint32>( 0, 1, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->Attach( m_entry2, sf::Rect<sf::Uint32>( 1, 1, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->Attach( m_label3, sf::Rect<sf::Uint32>( 0, 2, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->Attach( m_entry3, sf::Rect<sf::Uint32>( 1, 2, 1, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    m_table->Attach( m_button1, sf::Rect<sf::Uint32>( 0, 3, 2, 1 ), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));


    m_table->SetRowSpacings( 10.f );
    m_table->SetColumnSpacings( 10.f );

    m_window->Add( m_table );
}

void WindowLogIn::event(sf::Event& event)
{
    m_window->HandleEvent( event );
}

void WindowLogIn::step()
{
    m_window->Update( 0.f );

    if(code == 1)
    {
        delete m_socket;
        sfg::Context::Get().GetEngine().SetProperty("#Pseudo", "BorderColor", sf::Color(255, 100, 100, 255));
        cout << "Le pseudo est deja utilise" << endl;
        code = -1;
    }
}

void WindowLogIn::draw(sf::RenderWindow& window)
{

}

void WindowLogIn::onButtonClick()
{
        sfg::Context::Get().GetEngine().SetProperty("#Pseudo", "BorderColor", sf::Color(128, 128, 128, 255));

        m_socket = new sf::TcpSocket();

        ip = m_entry1->GetText();
        portString = m_entry2->GetText();
        std::string::size_type sz;
        port = std::stoi(portString, &sz);
        pseudo = m_entry3->GetText();

        sf::Socket::Status status = m_socket->connect(ip, port);
        if (status != sf::Socket::Done)
            cout << "Impossible de se connecter" << endl;
        else
            cout << "connexion etablie avec le serveur distant" << endl;


        m_data << 0 << pseudo;
        if (m_socket->send(m_data) != sf::Socket::Done)
            cout << "Impossible d'envoyer les donnees au serveur" << std::endl;
        else
            cout << "Envoie du pseudo" << endl;
        m_data.clear();


        if (m_socket->receive(m_data) != sf::Socket::Done)
            cout << "Erreur receive" << endl;
        m_data >> code;
        m_data.clear();

        if(code == 0)
            connected = true;

}

void WindowLogIn::show()
{
    m_window->Show(true);
    activated = true;
}

void WindowLogIn::hidden()
{
    m_window->Show(false);
    activated = false;
}

bool WindowLogIn::getActivated()
{
    return activated;
}

bool WindowLogIn::getConnected()
{
    return connected;
}
