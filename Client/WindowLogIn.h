#ifndef WINDOWLOGIN_H
#define WINDOWLOGIN_H
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

class WindowLogIn
{
    public:
        WindowLogIn(sf::TcpSocket* socket);
        virtual ~WindowLogIn();
        void create(sf::RenderWindow& window);
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);
        void onButtonClick();
        void show();
        void hidden();
        bool getActivated();
        bool getConnected();

    protected:

    private:
        sfg::Window::Ptr m_window;
        sfg::Table::Ptr m_table;
        sfg::Button::Ptr m_button1;
        sfg::Label::Ptr m_label1;
        sfg::Label::Ptr m_label2;
        sfg::Label::Ptr m_label3;
        sfg::Entry::Ptr m_entry1;
        sfg::Entry::Ptr m_entry2;
        sfg::Entry::Ptr m_entry3;

        sf::TcpSocket* m_socket;
        sf::Packet m_data;

        std::string ip;
        std::string portString;
        std::string pseudo;
        int port;
        int code;

        bool activated = true;
        bool connected = false;
};

#endif // WINDOWLOGIN_H
