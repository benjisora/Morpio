#include <iostream>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <string>
#include <thread>
#include <math.h>

using namespace std;

boolean addingPseudo(string, int);
bool horizontalWin(std::vector<int>, int, int, int, int, int);
bool verticalWin(std::vector<int>, int, int, int, int, int);
bool diagWin(std::vector<int>, int, int, int, int, int);
bool diagWin2(std::vector<int>, int, int, int, int, int);
bool GameThread(int, int, int, int, int);
std::vector<std::thread*> Threads;

std::vector<sf::TcpSocket*> clients; //Tableau de connexions de clients
std::vector<string> pseudos; //Tableau de pseudos relatifs aux clients (association par id)
int playerCreator = -1; //Joueur ayant les droits de création sur la partie

sf::SocketSelector selector;
int main()
{
    sf::Packet data; //Paquet d'envoi de données
    int code = 0; //Code d'erreur

    sf::TcpListener listener;
    listener.listen(6666); //Listener lié au port 6666

    selector.add(listener); //Selecteur lié au listener (pour permettre de réagir a toute connexion via ce listener)

    while (true)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener)) //Le listener est pret a accepter une connexion
            {

                sf::TcpSocket* client = new sf::TcpSocket(); //Création d'une nouvelle socket

                if (listener.accept(*client) == sf::Socket::Done) //Des qu'une connexion est effecutée
                {
                    clients.push_back(client);
                    selector.add(*clients[clients.size() - 1]); // Ajout du client au selecteur de telle sorte a ce qu'on puisse l'écouter

                    cout << "NOUVEAU CLIENT !! Nombre de clients: " << clients.size() << endl;

                    client->setBlocking(true);
                    string pseudo = "";

                    if (client->receive(data) != sf::Socket::Done)
                        cout << "ERREUR : echec de reception du pseudo" << endl;
                    data >> code >> pseudo;
                    data.clear();

                    boolean correctPseudo = addingPseudo(pseudo, code);
                    client->setBlocking(false);
                    if (pseudo == "")
                    {
                        pseudo = "SansNom";
                    }

                    if (correctPseudo && playerCreator == -1)
                        code = 101;
                    else if (correctPseudo && playerCreator != -1)
                        code = 0;
                    else
                        code = 1;
                    cout << code << endl;
                    pseudos.push_back(pseudo);
                    cout << "Nom: " << pseudos[pseudos.size() - 1] << endl;

                    if (!correctPseudo)
                    {
                        selector.remove(*clients[clients.size() - 1]);
                        clients.erase(clients.begin() + clients.size() - 1);
                        cout << "ERREUR : Client parti" << endl;
                        cout << "Nombre de clients: " << clients.size() << endl;
                    }

                    if (playerCreator == -1)
                    {
                        cout << "pseudos.size : " << pseudos.size() - 1 << endl;

                        playerCreator = pseudos.size() - 1;
                    }

                    data << code;
                    if (client->send(data) != sf::Socket::Done)
                        cout << "ERREUR : echec d'envoi du code" << endl;
                    data.clear();
                }
                else
                {
                    cout << "ERREUR : connexion non acceptee" << endl;
                }
            }
            else // La socket du listener n'est pas prete, on teste tous les autres sockets (clients)
            {

                for (int i = 0; i < clients.size(); i++)
                {
                    if (selector.isReady(*clients[i])) // Le client a fait quelque chose dans la socket
                    {

                        sf::Packet data2;
                        if (clients[i]->receive(data2) != sf::Socket::Disconnected)
                        {
                            if (i == playerCreator)
                            {
                                int nbJoueursPartie, tailleGrillePartie, scoreMinimal;
                                data2 >> code >> nbJoueursPartie >> tailleGrillePartie >> scoreMinimal;
                                data2.clear();

                                cout << "nb " << nbJoueursPartie << " taille " << tailleGrillePartie << " score " << scoreMinimal << endl;

                                if (code == 0)
                                {
                                    cout << nbJoueursPartie << " " << tailleGrillePartie << " " << scoreMinimal << endl;
                                    if ((tailleGrillePartie * tailleGrillePartie) >= pow(scoreMinimal, nbJoueursPartie) && //
                                            tailleGrillePartie > 0 && scoreMinimal > 0 && nbJoueursPartie > 1 && // Valeurs bonnes
                                            tailleGrillePartie <= 20 && nbJoueursPartie <= 6) //
                                    {
                                        cout << "tout est bon, debut : "<<playerCreator << endl;

                                        Threads.push_back(new std::thread(GameThread, playerCreator, (playerCreator + nbJoueursPartie),
                                                                          tailleGrillePartie, nbJoueursPartie, scoreMinimal));
                                        Threads[Threads.size()-1]->detach();
                                    }
                                    else
                                    {
                                        cout << "pas bon" << endl;
                                        data << 1;
                                        if (clients[i]->send(data) != sf::Socket::Done)
                                            cout << "ERREUR : echec d'envoi du code" << endl;
                                        data.clear();
                                    }
                                }
                            }
                        }
                        else // déconnexion du joueur i
                        {
                            cout << "DECONNEXION HORS THREAD" << endl;
                            if (i == playerCreator)
                                playerCreator = -1;
                            selector.remove(*clients[i]);
                            clients.erase(clients.begin()+i);
                            pseudos.erase(pseudos.begin()+i);
                            i--;
                            cout << "Nombre de clients: " << clients.size() << endl;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

boolean addingPseudo(string pseudo, int code)
{

    boolean pseudoAdded = false;

    if (code == 0) //si l'envoi est bon
    {
        boolean pseudoGood = true;
        for (unsigned int i = 0; i < pseudos.size(); i++)
        {
            if (pseudos[i] == pseudo)
            {
                pseudoGood = false;
                break;
            }
        }
        if (pseudoGood)
            pseudoAdded = true;
    }

    return pseudoAdded;
}

bool GameThread(int debut, int fin, int tailleGrillePartie, int nbJoueurs, int scoreMinimal)
{

    try
    {
        sf::Packet data;

        if (nbJoueurs > pseudos.size() - playerCreator)
        {
            data << 0;
            if (clients[debut]->send(data) != sf::Socket::Done)
                cout << "ERREUR : echec d'envoi du code" << endl;
            data.clear();
        }

        while (nbJoueurs > pseudos.size() - playerCreator || pseudos.size() == 0)
        {
        }

        cout << "j'ai assez de joueurs" << endl;
        for (int i = debut; i < fin; i++)
        {
            //selector.remove(*clients[i]);

            if (pseudos.size() != 0)
            {

                data << 5;

                if (clients[i]->send(data) != sf::Socket::Done)
                    cout << "ERREUR : echec d'envoi du code" << endl;
                data.clear();

                data << tailleGrillePartie;
                if (clients[i]->send(data) != sf::Socket::Done)
                    cout << "ERREUR : echec d'envoi du code" << endl;
                data.clear();
            }
        }
        if (playerCreator + nbJoueurs < pseudos.size() && pseudos.size() != 0)
        {
            playerCreator = (playerCreator + nbJoueurs);
            cout << "the first is " << playerCreator << endl;
            data << 101;

            if (clients[playerCreator]->send(data) != sf::Socket::Done)
                cout << "ERREUR : echec d'envoi du code" << endl;
            data.clear();
        }
        else
        {
            playerCreator = -1;
        }

        /**
        * CODE DU JEUUUU
        **/

        vector<int> grille;
        for (int i = 0; i < tailleGrillePartie * tailleGrillePartie; i++)
        {
            grille.push_back(-1);
        }
        for (int i = debut; i < fin; i++)
        {

            data << 7 << tailleGrillePartie;
            if (clients[i]->send(data) != sf::Socket::Done)
                cout << "ERREUR : echec d'envoi du code" << endl;
            data.clear();
        }
        for (int i = debut; i < fin; i++)
        {
            for (int j = debut; j < fin; j++)
            {
                data << 0 << j << pseudos[j];
                if (clients[i]->send(data) != sf::Socket::Done)
                    cout << "ERREUR : echec d'envoi du code" << endl;
                data.clear();
            }
        }
        for (int i = debut; i < fin; i++)
        {

            data << 8;
            if (clients[i]->send(data) != sf::Socket::Done)
                cout << "ERREUR : echec d'envoi du code" << endl;
            data.clear();
        }

        bool partiefinie = false;

        sf::Packet data2;
        int posX=0, posY=0, code=0;
        int tour = 0;
        while (!partiefinie)
        {

            for (int i = debut; i < fin; i++)
            {
                cout << "jenvoie 8 puis " << tour%(nbJoueurs)+debut << endl;
                data << 8 << tour%(nbJoueurs)+debut;

                if (clients[i]->send(data) != sf::Socket::Done)
                    cout << "ERREUR : echec d'envoi du code" << endl;
                data.clear();
            }

            bool positionGood = false;

            while(!positionGood)
            {

                data2.clear();

                sf::Socket::Status test = clients[tour%(nbJoueurs)+debut]->receive(data2);
                if (test == sf::Socket::Done)
                {
                    cout << "position reçue de " << tour%(nbJoueurs)+debut << endl;
                    data2 >> posX >> posY;
                    data2.clear();

                    if(grille[posX + tailleGrillePartie * posY]== -1 )
                    {

                        grille[posX + tailleGrillePartie * posY] = tour%(nbJoueurs)+debut;

                        for (int i = debut; i < fin; i++)
                        {
                            data << 11 << posX << posY;

                            if (clients[i]->send(data) != sf::Socket::Done)
                                cout << "ERREUR : echec d'envoi du code" << endl;
                            data.clear();
                        }

                        cout << "bonne position" << endl;


                        bool hWin = horizontalWin(grille,posX, posY, tour%(nbJoueurs)+debut, tailleGrillePartie, scoreMinimal);

                        bool vWin = verticalWin(grille,posX, posY, tour%(nbJoueurs)+debut, tailleGrillePartie, scoreMinimal);

                        bool dWin = diagWin(grille,posX, posY, tour%(nbJoueurs)+debut, tailleGrillePartie, scoreMinimal);
                        bool dWin2 = diagWin2(grille,posX, posY, tour%(nbJoueurs)+debut, tailleGrillePartie, scoreMinimal);


                        if(hWin || vWin || dWin || dWin2)
                        {
                            cout << "coup gagnant de la part de " << tour%(nbJoueurs)+debut << endl;
                            partiefinie = true;
                        }
                        tour++;

                        positionGood = true;

                    }
                    else
                    {

                        data << 10 << posX << posY;
                        if (clients[tour%(nbJoueurs)+debut]->send(data) != sf::Socket::Done)
                            cout << "ERREUR : echec d'envoi du code" << endl;
                        data.clear();

                    }
                }
                else if (test == sf::Socket::Disconnected)
                {
                    cout << "DECONNEXION INSIDE THREAD" << endl;
                    for (int i = debut; i < fin; i++)
                    {
                        selector.remove(*clients[i]);
                    }
                    return false;
                }
            }
        }
        cout << "BRAVOOOO" << endl;
        return true;
    }
    catch ( const std::bad_alloc & )
    {
        std::cerr << "Erreur : mémoire insuffisante.\n";
    }
    catch ( const std::out_of_range & )
    {
        std::cerr << "Erreur : débordement de mémoire.\n";
    }
}

//CHECK HORIZONTAL:
bool horizontalWin(std::vector<int> grille, int x, int y, int id, int tailleGrillePartie, int scoreMinimum)
{

    int valueID = 0;

    for (int i = 0; i < tailleGrillePartie; i++)
    {
        //cout << "idgrille[i+tailleGrillePartie*y] " << grille[i+tailleGrillePartie*y]<< endl;
        if (grille[i+tailleGrillePartie*y]==id)
        {

            valueID++;
            if(valueID == scoreMinimum)
            {
                cout << "horizontal" << endl;
                return true;
            }
        }
        else
        {
            valueID = 0;
        }
    }
    return false;
}

bool verticalWin(std::vector<int> grille, int x, int y, int id, int tailleGrillePartie, int scoreMinimum)
{

    int valueID = 0;

    for (int i = 0; i < tailleGrillePartie; i++)
    {
        //cout << "value " << valueID<< endl;
        if (grille[x+tailleGrillePartie*i]==id)
        {
            valueID++;


        }
        else
        {
            valueID = 0;
        }
        if(valueID == scoreMinimum)
        {
            cout << "vertical" << endl;
            return true;
        }
    }
    return false;
}

bool diagWin(std::vector<int> grille, int x, int y, int id, int tailleGrillePartie, int scoreMinimum)
{

    int copyX = x;
    int copyY = y;
    int valueID = 0;


    while(copyX > 0 && copyY > 0)
    {
        copyX--;
        copyY--;
    }

    while(copyX != tailleGrillePartie && copyY != tailleGrillePartie)
    {
        if (grille[copyX+tailleGrillePartie*copyY]==id)
        {
            valueID++;

            if(valueID == scoreMinimum)
            {
                cout << "diagLR" << endl;
                return true;
            }
        }
        else
        {
            valueID = 0;
        }
        copyX++;
        copyY++;
    }

    return false;
}

bool diagWin2(std::vector<int> grille, int x, int y, int id, int tailleGrillePartie, int scoreMinimum)
{

    int valueID = 0;
    int indexGrid = x+tailleGrillePartie*y;

    cout << "init: " <<indexGrid << endl;
    while(indexGrid > tailleGrillePartie)
    {

        indexGrid = indexGrid - (tailleGrillePartie -1);
        //cout << "remonte: " << indexGrid << endl;
    }

    do
    {

        if (grille[indexGrid]==id)
        {
            valueID++;

            if(valueID == scoreMinimum)
            {
                cout << "diagRL" << endl;
                return true;
            }
        }
        else
        {
            valueID = 0;
        }
        //cout << "descend: " << indexGrid << endl;
        indexGrid = indexGrid + tailleGrillePartie-1;
    }
    while(indexGrid < (tailleGrillePartie*tailleGrillePartie-tailleGrillePartie) && indexGrid%tailleGrillePartie != 0);

    if (grille[indexGrid]==id)
    {
        valueID++;

        if(valueID == scoreMinimum)
        {
            cout << "diagRL" << endl;
            return true;
        }
    }
    else
    {
        valueID = 0;
    }
    //cout << "descend: " << indexGrid << endl;

    return false;

    /*
    int copyX = x;
    int copyY = y;
    int valueID = 0;

    while(copyX < tailleGrillePartie-1 && copyY > 0)
    {
        copyX++;
        copyY--;
    }

    while(copyX != 0 && copyY != tailleGrillePartie)
    {
        if (grille[copyX+tailleGrillePartie*copyY]==id)
        {
            valueID++;

            if(valueID == scoreMinimum)
            {
                cout << "diagRL" << endl;
                return true;
            }
        }
        else
        {
            valueID = 0;
        }
        copyX--;
        copyY++;
    }


    return false;

    */



}
