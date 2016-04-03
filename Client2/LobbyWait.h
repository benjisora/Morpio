#ifndef LOBBYWAIT_H
#define LOBBYWAIT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))


class LobbyWait
{
    public:
        LobbyWait();
        virtual ~LobbyWait();
        void create();
        void step();
        void draw(sf::RenderWindow& window);

    protected:

    private:
        sf::Sprite spr1;
        sf::Texture tex1;
        sf::Sprite spr2;
        sf::Texture tex2;
        float a, v, X;
        float a2, v2, X2;
        bool sens;
        sf::Font font;
        sf::Text boxText;
        bool fadIn;
        int alpha;
        int previousMessage;
        std::vector<std::string> text;
};

#endif // LOBBYWAIT_H
