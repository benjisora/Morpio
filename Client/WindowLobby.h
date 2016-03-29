#ifndef WINDOWLOBBY_H
#define WINDOWLOBBY_H
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

class WindowLobby
{
    public:
        WindowLobby(sf::TcpSocket* socket);
        virtual ~WindowLobby();
        void create(sf::RenderWindow& window);
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);
        void onButtonClick1();
        void onButtonClick2();
        void show();
        void hidden();
        bool getActivated();

    protected:

    private:
        sfg::Window::Ptr m_window;
        sfg::Table::Ptr m_table;
        sfg::Button::Ptr m_button1;
        sfg::Button::Ptr m_button2;

        sf::TcpSocket* m_socket;
        sf::Packet m_data;

        int code;

        bool activated = true;
};

#endif // WINDOWLOBBY_H
