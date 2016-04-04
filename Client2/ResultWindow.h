#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Button.h"
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))

class ResultWindow
{
    public:
        ResultWindow();
        virtual ~ResultWindow();
        void create();
        void event(sf::Event& event);
        void step();
        void draw(sf::RenderWindow& window);
        void setText(std::string txt);
        void setTextToast(std::string txt);
        bool isClickedRetry();
        bool isClickedQuit();

    protected:

    private:
        sf::RectangleShape rect1;
        sf::RectangleShape rect2;

        Button button1;
        Button button2;

        float a, v, X;
        float a2, v2, X2;
        bool sens;
        sf::Font font;
        sf::Text boxText;
        sf::Text boxText2;
        bool fadIn;
        int alpha;
};

#endif // RESULTWINDOW_H
