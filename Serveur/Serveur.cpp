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
	listNickName = new std::map<int,std::string>();
	int nbClient = 0;
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

	std::string nickName = "unnamed";

	std::ostringstream oss;
	oss << nbClient;
	nickName+=oss.str();
	nickName+='\0';
	listNickName->insert(std::pair<int,std::string>(newSockfd,nickName));
	++nbClient;
	return newSockfd;
}

int Serveur::rerootToAll(const char*  message, const uint32_t size, int from)
{

  std::string nickName;
  nickName = listNickName->at(from);
  std::cout << nickName.c_str() << "-" << nickName.length()<< std::endl;
      uint32_t newSize=size+nickName.length();
      std::cout << newSize << std::endl;
 std::vector<int>::iterator it;
  for(it= listeClient->begin(); it != listeClient->end(); ++it)
    {
      char * newMessage = new char[newSize];
      uint32_t type_r=3;

      memcpy(newMessage,&newSize,sizeof(uint32_t));
      memcpy(newMessage+sizeof(uint32_t),&type_r, sizeof(uint32_t));
      memcpy(newMessage+sizeof(uint32_t)*2,nickName.c_str(), nickName.length());
      memcpy(newMessage+sizeof(uint32_t)*2+nickName.length(),message+sizeof(uint32_t)*2, size-sizeof(uint32_t)*2);
     
      write(*it, newMessage, newSize);
	
    }

}

int Serveur::rerootToOne(const char* message, uint32_t size, std::string nickName)
{

}
