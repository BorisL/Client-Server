/*
 * Serveur.hh
 *
 *  Created on: 22 mars 2013
 *      Author: Boris Liger
 */

#ifndef SERVEUR_HH_
#define SERVEUR_HH_

#include <vector>
#include <map>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdexcept>
#include <csignal>

int handler(int);

class Serveur
{
  // liste des file descriptor clients
  std::vector<int>* listeClient;
  // map file descripto / nick name des clients 
  std::map<int,std::string>* listNickName;
  // file descriptor serveur
	int socket_handler;
  // données serveur
  struct sockaddr_in mon_address;
  int addrlen;
  // nombre clients connectés
  int nbClient;
  
public:
  // consturcteur de Serveur 
  // @arg1 : port d'ecoute
  Serveur(int port);
  // destructeur pour de serveur
  virtual ~Serveur();
  // getter pour recuperer la socket serveur
  int getSocketHandler() const;
  // setter de la socket serveur
  void setSocketHandler(int socketHandler);
  // retourne la liste des clients 
  std::vector<int>* getListeClient() const;
  // definie la liste de serveur
  void setListeClient(std::vector<int>* listeClient);
  // accepter un client
  int acceptClient();
  // re root un message vers la liste des clients
  int rerootToAll(const char*,const uint32_t, int);
  // root un message vers un client (non implementé)
  int rerootToOne(const char*,uint32_t, std::string);
  // changer le nickname d'un client
  int changeNickname(int, char*);

};

#endif /* SERVEUR_HH_ */
