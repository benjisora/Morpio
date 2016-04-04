#include "LoginWindow.h"
#include <sstream>
#include <string>

LoginWindow::LoginWindow()
{

}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::create()
{
    if (!font.loadFromFile("res/Exo-Regular.otf"))
    {
        std::cout << "error font" << std::endl;
    }
    if (!font2.loadFromFile("res/Exo-Light.otf"))
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
    credit.setString("Tous droit reserv�s\n    Mobi Benjisora");




    input1.create(sf::Vector2f(800,100), "Adresse");
    input1.setTrickness(0);
    input1.setMaxLength(15);
    input1.setText("172.31.247.41");

    input2.create(sf::Vector2f(800,150), "Port");
    input2.setTrickness(0);
    input2.setMaxLength(5);
    input2.setText("6666");

    input3.create(sf::Vector2f(800,200), "Pseudo");
    input3.setTrickness(0);
    input3.setMaxLength(14);

    button.create(sf::Vector2f(800, 250), sf::Vector2f(192, 46), "Connexion");
}

void LoginWindow::event(sf::Event& event)
{
    input1.event(event);
    input2.event(event);
    input3.event(event);

    button.event(event);
}

void LoginWindow::step()
{
    input1.step();
    input2.step();
    input3.step();

    button.step();
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

bool LoginWindow::isClicked()
{
    return button.isClicked();
}

std::string LoginWindow::getIp()
{
    return input1.getText();
}

int LoginWindow::getPort()
{
    std::stringstream sstr{input2.getText()};
    int value;
    sstr >> value;
    return value;
}

std::string LoginWindow::getPseudo()
{
    return input3.getText();
}