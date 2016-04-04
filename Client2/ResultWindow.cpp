#include "ResultWindow.h"

ResultWindow::ResultWindow()
{
    //ctor
}

ResultWindow::~ResultWindow()
{
    //dtor
}

void ResultWindow::create()
{
    rect1.setFillColor(sf::Color(200,200,200));
    rect1.setSize(sf::Vector2f(1024, 30));
    rect1.setPosition(0, 600);

    rect2.setFillColor(sf::Color(200,200,200));
    rect2.setSize(sf::Vector2f(1024, 30));
    rect2.setPosition(0, 300);

    a = 0;
    a2 = 0;
    alpha = 0;
    sens = true;
    fadIn = true;



    if (!font.loadFromFile("res/Exo-Regular.otf"))
    {
        std::cout << "error font" << std::endl;
    }

    boxText.setFont(font);
    boxText.setString("YEAAAAAH");
    boxText.setCharacterSize(50);
    boxText.setStyle(sf::Text::Bold);
    boxText.setColor(sf::Color(255,255,255,255));
    boxText.setOrigin(boxText.getLocalBounds().width/2, boxText.getLocalBounds().height/2);
    boxText.setPosition(1024/2,768/2);

    boxText2.setFont(font);
    boxText2.setString("");
    boxText2.setCharacterSize(30);
    boxText2.setStyle(sf::Text::Bold);
    boxText2.setColor(sf::Color(255,255,255,255));
    boxText2.setOrigin(boxText2.getLocalBounds().width/2, boxText2.getLocalBounds().height/2);
    boxText2.setPosition(1024/2,550);

    button1.create(sf::Vector2f(240, 650), sf::Vector2f(192, 46), "   Rejouer");
    button2.create(sf::Vector2f(600, 650), sf::Vector2f(192, 46), "    Quitter");
}

void ResultWindow::event(sf::Event& event)
{
    button1.event(event);
    button2.event(event);
}

void ResultWindow::step()
{
    if(sens == true)
    {
        a++;
        v = a /120;
        v = SMOOTHSTEP(v);
        X = (0 * v) + (600 * (1 - v));
        if(a == 120)
            sens = false;
        rect1.setPosition(sf::Vector2f(-X/*+200*/, 475));
    }


    if(fadIn == true)
    {
        a2++;
        v2 = a2 / 120;
        v2 = SMOOTHSTEP(v2);
        X2 = (0 * v2) + (600 * (1 - v2));
        if(a2 == 120)
        {
            fadIn = false;
        }

        rect2.setPosition(sf::Vector2f(X/*-200*/, 300));

    }

    button1.step();
    button2.step();

}

void ResultWindow::draw(sf::RenderWindow& window)
{
    window.draw(rect1);
    window.draw(rect2);
    window.draw(boxText);
    window.draw(boxText2);

    button1.draw(window);
    button2.draw(window);
}

void ResultWindow::setText(std::string txt)
{
    boxText.setString(txt);
    boxText.setOrigin(boxText.getLocalBounds().width/2, boxText.getLocalBounds().height/2);
}

void ResultWindow::setTextToast(std::string txt)
{
    boxText2.setString(txt);
    boxText2.setOrigin(boxText2.getLocalBounds().width/2, boxText2.getLocalBounds().height/2);
}

bool ResultWindow::isClickedRetry()
{
    return button1.isClicked();
}

bool ResultWindow::isClickedQuit()
{
    return button2.isClicked();
}
