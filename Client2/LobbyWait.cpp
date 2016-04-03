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
    spr1.setPosition(1024/2, 728/2-40);

    tex2.loadFromFile("wait.png");
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


    if (!font.loadFromFile("Exo-Regular.otf"))
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

    text.push_back("Rotater le chargement");
    text.push_back("Ajout de booster");
    text.push_back("Recherche du dernier post 9gag");
    text.push_back("Analyse du tobydélice");
    text.push_back("Appliquer les couleurs quantiques");
    text.push_back("Démêlage de la mémoire vive");
    text.push_back("Etirer le processeur");
    text.push_back("Extraire les données personelles");
    text.push_back("Creuser le fromage");
    text.push_back("Recherche du majora's mask");
    text.push_back("Alignement de la grille frequentielle");
    text.push_back("Accorder les instruments de mesure");
    text.push_back("Lecture des citations usb");
    text.push_back("Polir le gravier");
    text.push_back("Diagnostiquer le bug entre l'écran et la chaise");
    text.push_back("Nettoyage de l'accordéon");
    text.push_back("Standardiser les boules de Goo");
    text.push_back("Générer un MVC séquentiel");
    text.push_back("Estimer le temps d'attente");

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
