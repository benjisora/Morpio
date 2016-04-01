#ifndef LOBBYWAIT_H
#define LOBBYWAIT_H
#include <SFML/Graphics.hpp>
#include <iostream>
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
        float a;
        float v, X;
        bool sens;

};

#endif // LOBBYWAIT_H
