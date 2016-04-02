#include "GameCreateWindow.h"
#include <sstream>
#include <string>

GameCreateWindow::GameCreateWindow()
{

}

GameCreateWindow::~GameCreateWindow()
{

}

void GameCreateWindow::create()
{

    if (!font.loadFromFile("Exo-Regular.otf"))
    {
        std::cout << "Error font: can't find \"Exo-Regular.otf\"." << std::endl;
    }
    if (!font2.loadFromFile("Exo-Light.otf"))
    {
        std::cout << "Error font: can't find \"Exo-Light.otf\"." << std::endl;
    }

    boxText.setFont(font);
    boxText.setCharacterSize(22.5);
    boxText.setStyle(sf::Text::Bold);
    boxText.setColor(sf::Color(255,255,255,255));
    boxText.setPosition(805,40);
    boxText.setString("Créer une partie");

    credit.setFont(font2);
    credit.setCharacterSize(14);
    credit.setColor(sf::Color(80,80,80,255));
    credit.setPosition(830,700);
    credit.setString("Tous droits reservés\n    Mobi - Benjisora");




    input1.create(sf::Vector2f(800,100), "Nombre de joueurs");
    input1.setTrickness(0);
    input1.setMaxLength(15);
    input1.setText("2");

    input2.create(sf::Vector2f(800,150), "Taille de la grille");
    input2.setTrickness(0);
    input2.setMaxLength(5);
    input2.setText("3");

    input3.create(sf::Vector2f(800,200), "Score minimal");
    input3.setTrickness(0);
    input3.setMaxLength(14);
    input3.setText("3");

    button.create(sf::Vector2f(800, 250), sf::Vector2f(192, 46), "     Créer");
}

void GameCreateWindow::event(sf::Event& event)
{
    input1.event(event);
    input2.event(event);
    input3.event(event);

    button.event(event);
}

void GameCreateWindow::step()
{
    input1.step();
    input2.step();
    input3.step();

    button.step();
}

void GameCreateWindow::draw(sf::RenderWindow& window)
{
    window.draw(boxText);

    input1.draw(window);
    input2.draw(window);
    input3.draw(window);

    button.draw(window);

    window.draw(credit);
}

bool GameCreateWindow::isClicked()
{
    return button.isClicked();
}

int GameCreateWindow::getNbPlayer()
{
    std::stringstream sstr{input1.getText()};
    int value;
    sstr >> value;
    return value;
}

int GameCreateWindow::getSizeGrid()
{
    std::stringstream sstr{input2.getText()};
    int value;
    sstr >> value;
    return value;
}

int GameCreateWindow::getScoreMin()
{
    std::stringstream sstr{input3.getText()};
    int value;
    sstr >> value;
    return value;
}
