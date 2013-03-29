/*
 * Serveur.cpp
 *
 *  Created on: 22 mars 2013
 *      Author: p13amjad
 */

#include "Serveur.hh"

Serveur::Serveur(int port)
{
	listeClient = new std::vector<int>();


	bzero(&mon_address,sizeof(mon_address));
	mon_address.sin_port = htons(port);
	mon_address.sin_family = AF_INET;
	mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

	socket_handler = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(socket_handler,(struct sockaddr *)&mon_address,sizeof(mon_address));

	listen(socket_handler,5);
	addrlen = sizeof(mon_address);

}

Serveur::~Serveur()
{

}

int Serveur::getSocketHandler() const {
	return socket_handler;
}

void Serveur::setSocketHandler(int socketHandler) {
	socket_handler = socketHandler;
}

std::vector<int>* Serveur::getListeClient() const {
	return listeClient;
}

void Serveur::setListeClient(std::vector<int>* listeClient) {
	this->listeClient = listeClient;
}

int Serveur::acceptClient()
{

	int newSockfd=accept(socket_handler,
			(struct sockaddr *) &mon_address,
			(socklen_t*) &addrlen);

	if(newSockfd > -1)
		listeClient->push_back(newSockfd);
	std::cout << "Ajout socket num: " <<newSockfd << std::endl;

	return newSockfd;
}
