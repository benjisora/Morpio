#include "LoginWindow.h"

LoginWindow::LoginWindow()
{

}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::create()
{



    if (!font.loadFromFile("Exo-Regular.otf"))
    {
        std::cout << "error font" << std::endl;
    }
    if (!font2.loadFromFile("Exo-Light.otf"))
    {
        std::cout << "error font" << std::endl;
    }

    boxText.setFont(font);
    boxText.setCharacterSize(22.5);
    boxText.setStyle(sf::Text::Bold);
    boxText.setColor(sf::Color(255,255,255,255));
    boxText.setPosition(825,40);
    boxText.setString("Se connecter");

    credit.setFont(font2);
    credit.setCharacterSize(14);
    credit.setColor(sf::Color(80,80,80,255));
    credit.setPosition(830,700);
    credit.setString("Tous droit reservés\n    Mobi Benjisora");




    input1.create(sf::Vector2f(800,100), "Adresse");
    input1.setTrickness(0);
    input1.setMaxLength(15);

    input2.create(sf::Vector2f(800,150), "Port");
    input2.setTrickness(0);
    input2.setMaxLength(5);

    input3.create(sf::Vector2f(800,200), "Pseudo");
    input3.setTrickness(0);
    input3.setMaxLength(14);

    button.create(sf::Vector2f(800, 250), sf::Vector2f(192, 46));
}

void LoginWindow::event(sf::Event& event)
{
    input1.event(event);
    input2.event(event);
    input3.event(event);

    button.step();
}

void LoginWindow::step()
{
    input1.step();
    input2.step();
    input3.step();
}

void LoginWindow::draw(sf::RenderWindow& window)
{
    window.draw(boxText);

    input1.draw(window);
    input2.draw(window);
    input3.draw(window);

    button.draw(window);

    window.draw(credit);
}
