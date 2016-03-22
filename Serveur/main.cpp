#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <string>
#include <thread>


using namespace std;

void addingPseudo(std::vector<string>& pseudos, sf::TcpSocket* client, int idClient)
{

    boolean pseudoAdded = false;

    string pseudo = "";
    int code = 0;
    sf::Packet packet;
    sf::Packet data;

    client->setBlocking(true);

    while(!pseudoAdded)
    {

        if (client->receive(packet) != sf::Socket::Done)
        {
            cout << "echec de reception du pseudo" <<endl;
        }
        packet >> code >> pseudo;
        packet.clear();

        if(idClient==0 && code == 0) //si il y a aucun pseudo
        {
            cout << "premier" <<endl;
            pseudoAdded = true;
            code = 101;
        }
        else if(idClient != 0 && code == 0) //si il y a déjà des pseudos
        {
            boolean pseudoGood = true;
            for (unsigned int i=0; i<pseudos.size(); i++)
            {
                cout << "pas premier" <<endl;
                if(pseudos[i] == pseudo)
                {
                    cout << "pseudo egal!!" <<endl;
                    pseudoGood = false;
                    code = 1;
                    data << code;
                    if(client->send(data) != sf::Socket::Done)
                    {
                        cout << "echec d'envoi du code" <<endl;
                    }
                    data.clear();
                    break;
                }
            }
            if(pseudoGood)
            {
                cout << "valide !!!" <<endl;
                pseudoAdded = true;
                code = 0;
            }
        }
    }

    pseudos.push_back(pseudo);
    cout << "Pseudo: " << pseudos[idClient] << endl;

    data << code;
    if(client->send(data) != sf::Socket::Done)
    {
        cout << "echec d'envoi du code" <<endl;
    }
    data.clear();
}



int main()
{
    sf::Packet data;
    int code = 0;
    std::vector<sf::TcpSocket*> clients;
    std::vector<string> pseudos;

    int idClient = 0;

    sf::TcpListener listener;
    listener.listen(80); //création du listener et écoute du port
    sf::SocketSelector selector;
    selector.add(listener); //Création du select, et ajout du listener au select

    while (true)
    {
        // On attend un message d'une des sockets
        if (selector.wait())
        {
            // Test du listener
            if (selector.isReady(listener))  // Il y a une connexion en attente
            {
                sf::TcpSocket* client = new sf::TcpSocket();

                if (listener.accept(*client) == sf::Socket::Done)
                {
                    clients.push_back(client);

                    selector.add(*clients[clients.size()-1]); // Ajout du client au selecteur de telle sorte a ce qu'on puisse l'écouter

                    cout << "NOUVEAU CLIENT !! Nombre de clients: " << clients.size() << endl;

                    addingPseudo(pseudos, client, idClient);

                    client->setBlocking(false);
                    idClient++;

                }
                else
                {
                    cout<<"connexion non acceptee"<<endl;
                }
            }
            else  // La socket du listener n'est pas prete, on teste tous les autres sockets (clients)
            {
                int limit = clients.size();
                for (int i=0; i < limit; i++)
                {
                    if (selector.isReady(*clients[i]))
                    {
                        // Le client a fait quelque chose dans la socket

                        sf::Packet data2;

                        if (clients[i]->receive(data2) != sf::Socket::Disconnected)
                        {

                        }
                        else
                        {
                            cout << pseudos[i] << " est parti" << endl;

                            selector.remove(*clients[i]);
                            clients.erase(clients.begin()+i);
                            pseudos.erase(pseudos.begin()+i);
                            i--;
                            limit--;
                            idClient--;
                            cout << "Nombre de clients: " << clients.size() << endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
