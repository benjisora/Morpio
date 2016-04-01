#include <iostream>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <string>
#include <thread>

using namespace std;

boolean addingPseudo(std::vector<string>&, string, int);

void Lobby(/*std::vector<string>, int, std::vector<sf::TcpSocket*>*/ int, int, int);

string Partie(std::vector<sf::TcpSocket*>, std::vector<string>);

int main()
{
    sf::Packet data;
    int code = 0;
    std::vector<sf::TcpSocket*> clients;
    std::vector<string> pseudos;
    sf::Packet packet;

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

                    client->setBlocking(true);
                    string pseudo = "";

                    if (client->receive(packet) != sf::Socket::Done)
                        cout << "ERREUR : echec de reception du pseudo" <<endl;
                    packet >> code >> pseudo;
                    packet.clear();

                    boolean correctPseudo = addingPseudo(pseudos, pseudo, code);
                    client->setBlocking(false);

                    if(correctPseudo && clients.size()==1)
                        code = 101;
                    else if (correctPseudo && clients.size()!=1)
                        code = 0;
                    else
                        code = 1;

                    pseudos.push_back(pseudo);
                    cout << "Nom: " << pseudos[pseudos.size()-1] << endl;

                    if(!correctPseudo)
                    {
                        selector.remove(*clients[clients.size()-1]);
                        clients.erase(clients.begin()+clients.size()-1);
                        cout << "ERREUR : Client parti"<< endl;
                        cout << "Nombre de clients: " << clients.size() << endl;
                    }

                    data << code;
                    if(client->send(data) != sf::Socket::Done)
                        cout << "ERREUR : echec d'envoi du code" <<endl;
                    data.clear();

                    std::thread t1(Lobby, 1,2,3);
                    t1.detach();

                }
                else
                {
                    cout<<"ERREUR : connexion non acceptee"<<endl;
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

                        if(i==0)
                        {
                            sf::Packet data2;
                            int nbJoueursPartie, tailleGrillePartie, scoreMinimal;

                            if (clients[i]->receive(data2) != sf::Socket::Disconnected)
                            {
                                data2 >> code >> nbJoueursPartie >> tailleGrillePartie >> scoreMinimal;
                                if(code == 0)
                                    cout << nbJoueursPartie << " " << tailleGrillePartie << " " << scoreMinimal << endl;
                            }

                            else // déconnexion du joueur i
                            {
                                cout << pseudos[i] << " est parti" << endl;

                                selector.remove(*clients[i]);
                                clients.erase(clients.begin()+i);
                                pseudos.erase(pseudos.begin()+i);
                                i--;
                                limit--;
                                cout << "Nombre de clients: " << clients.size() << endl;
                            }
                        }

                    }
                }
            }
        }
    }

    return 0;
}

boolean addingPseudo(std::vector<string>& pseudos, string pseudo, int code)
{

    boolean pseudoAdded = false;

    if(code == 0) //si l'envoi est bon
    {
        boolean pseudoGood = true;
        for (unsigned int i=0; i<pseudos.size(); i++)
        {
            if(pseudos[i] == pseudo)
            {
                pseudoGood = false;
                break;
            }
        }
        if(pseudoGood)
            pseudoAdded = true;
    }

    return pseudoAdded;
}


void Lobby(/*std::vector<string> pseudos, int position, std::vector<sf::TcpSocket*> clients*/ int a, int b, int c)
{
   cout << "coucou" << endl;
   Sleep(5000);
   cout << "fini ?" << endl;
}

string Partie(std::vector<sf::TcpSocket*> clients, std::vector<string> pseudos)
{
    return "";
}
