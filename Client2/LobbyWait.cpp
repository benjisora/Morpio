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
    tex1.loadFromFile("res/wait2.png");
    //tex1.setSmooth(true);
    spr1.setTexture(tex1);
    spr1.setOrigin(spr1.getGlobalBounds().width/2.f, spr1.getGlobalBounds().height/2.f);
    spr1.setPosition(1024/2, 728/2-40);

    tex2.loadFromFile("res/wait.png");
    tex2.setSmooth(true);
    spr2.setTexture(tex2);
    spr2.setOrigin(spr2.getGlobalBounds().width/2.f, spr2.getGlobalBounds().height/2.f);
    spr2.setPosition(1024/2, 728/2-40);

    a = 0;
    a2 = 0;
    alpha = 0;
    sens = true;
    fadIn = true;
    previousMessage = -1;


    if (!font.loadFromFile("res/Exo-Regular.otf"))
    {
        std::cout << "error font" << std::endl;
    }

    boxText.setFont(font);
    boxText.setString("Recherche de joueurs");
    boxText.setCharacterSize(30);
    boxText.setStyle(sf::Text::Bold);
    boxText.setColor(sf::Color(255,255,255,255));
    boxText.setOrigin(boxText.getLocalBounds().width/2, 0);
    boxText.setPosition(1024/2,600);

    text.push_back("Rotation du chargement");
    text.push_back("Ajout de reacteurs");
    text.push_back("Lecture du dernier post 9Gag");
    text.push_back("Analyse du tobydélice");
    text.push_back("Application des couleurs quantiques");
    text.push_back("Démêlage de la mémoire vive");
    text.push_back("Etirement du processeur");
    text.push_back("Extraction des données personelles");
    text.push_back("Acquisition d'Excalibur");
    text.push_back("Envoi du signal a Batman");
    text.push_back("Allumage de la machine a Internet");
    text.push_back("Découverte du Saint Graal");
    text.push_back("Recherche de benji pour qu'il lance le serveur");
    text.push_back("Alignement de la grille frequentielle");
    text.push_back("Accordage des instruments de mesure");
    text.push_back("Lecture des citations USB");
    text.push_back("Polissage du gravier");
    text.push_back("Diagnostique du bug entre l'écran et la chaise");
    text.push_back("Nettoyage de l'accordéon");
    text.push_back("Standardisation des boules de Goo");
    text.push_back("Génération du MVC séquentiel");
    text.push_back("Estimation du temps d'attente");
    text.push_back("Lustrage de la moustache d'Hercule Poirot");
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


    if(fadIn == true)
    {
        a2++;
        v2 = a2 / 240;
        v2 = SMOOTHSTEP(v2);
        X2 = (0 * v2) + (255 * (1 - v2));
        if(a2 == 240)
        {
            fadIn = false;
            boxText.setString(text[rand()%text.size()]);
            boxText.setOrigin(boxText.getLocalBounds().width/2, 0);
        }

        boxText.setColor(sf::Color(200,200,200,X2));

    }
    if(fadIn == false)
    {
        a2--;
        v2 = a2 / 240;
        v2 = SMOOTHSTEP(v2);
        X2 = (0 * v2) + (255 * (1 - v2));
        if(a2 == 0)
            fadIn = true;
        boxText.setColor(sf::Color(200,200,200,X2));
    }

}

void LobbyWait::draw(sf::RenderWindow& window)
{
    window.draw(spr1);
    window.draw(spr2);
    window.draw(boxText);
}
