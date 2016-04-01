#include "LobbyWait.h"

LobbyWait::LobbyWait()
{
    //ctor
}

LobbyWait::~LobbyWait()
{
    //dtor
}

void LobbyWait::create()
{
    tex1.loadFromFile("wait2.png");
    //tex1.setSmooth(true);
    spr1.setTexture(tex1);
    spr1.setOrigin(spr1.getGlobalBounds().width/2.f, spr1.getGlobalBounds().height/2.f);
    spr1.setPosition(1024/2, 728/2);

    tex2.loadFromFile("wait.png");
    tex2.setSmooth(true);
    spr2.setTexture(tex2);
    spr2.setOrigin(spr2.getGlobalBounds().width/2.f, spr2.getGlobalBounds().height/2.f);
    spr2.setPosition(1024/2, 728/2);

    a = 0;
    sens = true;
}

void LobbyWait::step()
{
    if(sens == true)
    {
        a++;
        v = a / 360;
        v = SMOOTHSTEP(v);
        X = (0 * v) + (360 * (1 - v));
        if(a == 360)
            sens = false;
        spr2.setRotation(X);

    }
    if(sens == false)
    {
        a--;
        v = a / 360;
        v = SMOOTHSTEP(v);
        X = (360 * v) + (0 * (1 - v));
        if(a == 0)
            sens = true;
        spr2.setRotation(-X);
    }

}

void LobbyWait::draw(sf::RenderWindow& window)
{
    window.draw(spr1);
    window.draw(spr2);
}
