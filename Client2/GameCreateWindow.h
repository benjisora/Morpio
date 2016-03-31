#ifndef GAMECREATEWINDOW_H
#define GAMECREATEWINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "InputText.h"
#include "Button.h"



class GameCreateWindow
{
    public:
        GameCreateWindow();
        virtual ~GameCreateWindow();
        void create();
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);

    protected:

    private:
        InputText input1;
        InputText input2;
        InputText input3;

        Button button;

        sf::Font font, font2;
        sf::Text boxText, credit;
};

#endif // GAMECREATEWINDOW_H
