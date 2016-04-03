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
void GameThread(int, int, int, int, int);

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
                                        cout << "tout est bon" << endl;
                                        std::thread t1(GameThread, playerCreator, (playerCreator + nbJoueursPartie),
                                                       tailleGrillePartie, nbJoueursPartie, scoreMinimal);
                                        t1.detach();
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
                            cout << "DECONNEXION" << endl;
                            cout << pseudos[i] << " est parti" << endl;
                            if (i == playerCreator)
                                playerCreator = -1;
                            selector.remove(*clients[i]);
                            clients.erase(clients.begin() + i);
                            pseudos.erase(pseudos.begin() + i);
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

void GameThread(int debut, int fin, int tailleGrillePartie, int nbJoueurs, int scoreMinimal)
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

    for (int i = debut; i < fin; i++)
    {
        selector.remove(*clients[i]);

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
    int tour = debut;

    while (!partiefinie)
    {

        for (int i = debut; i < fin; i++)
        {
            data << 8 << tour%(debut+nbJoueurs);

            if (clients[i]->send(data) != sf::Socket::Done)
                cout << "ERREUR : echec d'envoi du code" << endl;
            data.clear();
        }


        bool positionGood = false;
        while(!positionGood)
        {
            data2.clear();
            if (clients[tour%(debut+nbJoueurs)]->receive(data2) == sf::Socket::Done)
            {
                data2 >> posX >> posY;
                data2.clear();
                code = 0;

                if(grille[posX + tailleGrillePartie * posY]== -1 )
                {
                    grille[posX + tailleGrillePartie * posY] = tour%(debut+nbJoueurs);

                    for (int i = debut; i < fin; i++)
                    {
                        data << 11 << posX << posY;

                        if (clients[i]->send(data) != sf::Socket::Done)
                            cout << "ERREUR : echec d'envoi du code" << endl;
                        data.clear();
                    }

                    tour++;
                    positionGood = true;

                }
                else
                {
                    data << 10 << posX << posY;
                    if (clients[tour%(debut+nbJoueurs)]->send(data) != sf::Socket::Done)
                        cout << "ERREUR : echec d'envoi du code" << endl;
                    data.clear();
                }
            }
            else
            {

            }
        }
    }
}
