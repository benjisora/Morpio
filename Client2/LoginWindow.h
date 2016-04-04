#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <SFML/Graphics.hpp>
#include <string>
#include "InputText.h"
#include "Button.h"
#include <iostream>
#include "Network.h"


class LoginWindow
{
    public:
        LoginWindow();
        virtual ~LoginWindow();
        void create();
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);
        bool isClicked();
        std::string getIp();
        int getPort();
        std::string getPseudo();

    protected:

    private:
        InputText input1;
        InputText input2;
        InputText input3;

        Button button;

        sf::Font font, font2;
        sf::Text boxText, credit;
};

#endif // LOGINWINDOW_H