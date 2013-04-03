/*
 * main.cpp
 *
 *  Created on: 22 mars 2013
 *      Author: p13amjad
 */
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdexcept>
#include "Serveur.hh"

int main (int argc, char** argv)
{


	Serveur* serveur = new Serveur(atoi(argv[1]));
	signal(SIGPIPE, SIG_IGN);

	struct timeval tv;
	fd_set readfds;

	while(true)
	{

		FD_ZERO(&readfds);
		FD_SET(serveur->getSocketHandler(), &readfds);
		int maxSocket = serveur->getSocketHandler();
		std::vector<int>::iterator it;
		std::vector<int>* clients = serveur->getListeClient();
		for(it= clients->begin(); it != clients->end(); ++it)
		{
			if((*it)>maxSocket)
				maxSocket=*it;
			FD_SET(*it, &readfds);
			std::cout << "\tSocket:" << *it << std::endl;
		}

		tv.tv_sec = 5;
		tv.tv_usec = 0;
		std::cout << maxSocket << std::endl;
		int sock = select(maxSocket+1, &readfds, NULL, NULL, &tv);
		if(sock < 0)
		{
			throw std::runtime_error("Erreur sur le select <0");
		}
		if(sock == 0)
		{
			continue;
		}
		// reception d'une demande de nouvelle connexion
		if(FD_ISSET(serveur->getSocketHandler(), &readfds))
		{
			serveur->acceptClient();
			//std::cout << "Nouveau client" << std::endl;
		}
		// parcours de la liste des clients connectés
		for(it= clients->begin(); it != clients->end(); ++it)
		{
			// reception d'un message client
			if(FD_ISSET(*it, &readfds))
			{
				std::cout << "Nouveau message reçu" << std::endl;
				char buff [100];
				memset(buff,0,100);
				int size=100;
				int recv_c = recv(*it,buff,size,0);
				uint32_t size_m=0;
				uint32_t type_m=0;
				memcpy(&size_m,buff,sizeof(uint32_t));
				memcpy(&type_m,buff+sizeof(uint32_t),sizeof(uint32_t));
				std::cout << size_m << std::endl;
				std::cout << type_m << std::endl;
				std::cout << buff+sizeof(uint32_t)*2<< "(" << recv_c << ")" << std::endl;

				switch(type_m)
				{
				case 1:
					// message texte
				  serveur->rerootToAll(buff,size_m,*it);
				  break;
				case 2:
					// changement de pseudo
					break;

				case 255:
					// ping
					break;
				}

			}
		}
	}

}



