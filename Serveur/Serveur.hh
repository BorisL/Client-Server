/*
 * Serveur.hh
 *
 *  Created on: 22 mars 2013
 *      Author: p13amjad
 */

#ifndef SERVEUR_HH_
#define SERVEUR_HH_

#include <vector>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdexcept>

class Serveur
{
	std::vector<int>* listeClient;
	int socket_handler;
	struct sockaddr_in mon_address;
	int addrlen;
public:
	Serveur(int port);
	virtual ~Serveur();

	int getSocketHandler() const;

	void setSocketHandler(int socketHandler);

	std::vector<int>* getListeClient() const;

	void setListeClient(std::vector<int>* listeClient);

	int acceptClient();
};

#endif /* SERVEUR_HH_ */
