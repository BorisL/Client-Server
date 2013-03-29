/*
 * main.cpp
 *
 *  Created on: 20 mars 2013
 *      Author: p13amjad
 */

#include <stdlib.h>
#include <stdexcept>
#include "Socket.hh"
#include "Message.hh"

int main (int argc, char** argv)
{

	if(argc < 3)
	{
		std::cout << "utilisation: ./Client host port [option]" << std::endl;
		std::cout << "\t [option]:" << std::endl;
		std::cout << "\t\t -v : afficher les info de debug" << std::endl;
		std::cout << "\t\t -n pseudo : indiquer le pseudo à utiliser" << std::endl;
		exit(-1);
	}
	bool debugMode = false;
	Socket* socket = new Socket(argv[1],atoi(argv[2]));

	for(int i=3; i<argc; ++i)
	{
		if(strcmp(argv[i],"-v")==0)
			debugMode=true;
		if(strcmp(argv[i],"-n")==0)
		{
			Message* message = new Message(2,argv[i+1]);
			socket->writeMessage(message);
		}
	}
	std::string in=" ";

	struct timeval tv;
	fd_set readfds;
	int stdin=STDIN_FILENO;

	;

	bool quit = false;

	do
	{
		FD_ZERO(&readfds);
		FD_SET(socket->getSocket(), &readfds);
		FD_SET(stdin, &readfds);
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		int sock = select(socket->getSocket()+1, &readfds, NULL, NULL, &tv);
		if(sock < 0)
		{
			throw std::runtime_error("Erreur sur le select");
		}
		if(sock == 0)
		{
			// en cas de timeout du select on envoie un ping pour verifier l'état du serveur
			//Message* message = new Message(255,"");
			//socket->writeMessage(message);
			if(debugMode)
				std::cout << "Envoie de PING vers le serveur "<< std::endl;

		}
		else
		{
			if(debugMode)
				std::cout << "SOCK " << sock << " " << FD_ISSET(socket->getSocket(), &readfds) << " " << FD_ISSET(stdin, &readfds) << std::endl;
			if(FD_ISSET(socket->getSocket(), &readfds))
			{
				char buff [100];
				memset(buff,0,100);
				int size=100;
				int recv_c = recv(socket->getSocket(),buff,size,0);
				if(debugMode) std::cout << "RECV " << recv_c << std::endl;
				if(recv_c == -1)
					exit(99);
				uint32_t size_m=0;
				uint32_t type_m=0;

				memcpy(&size_m,buff,sizeof(uint32_t));
				memcpy(&type_m,buff+sizeof(uint32_t),sizeof(uint32_t));

				if(type_m==255)
				{
					if(debugMode) std::cout << "Ping from server" << std::endl;

				}
				if(type_m==3)
				{
					int size_nickname =  strlen(buff+sizeof(uint32_t)*2);
					std::cout << "recv from socket: < " << size_m << " >" << std::endl;
					std::cout << "recv from socket: < " << type_m << " >" << std::endl;
					std::cout << "recv from socket: < " << buff+sizeof(uint32_t)*2 << " >" << std::endl;
					std::cout << "recv from socket: < " << buff+sizeof(uint32_t)*2+size_nickname+1 << " >" << std::endl;
					std::cout << std::endl;
				}
				if(type_m==4)
				{
					uint32_t accept_m=0;
					memcpy(&accept_m,buff+(sizeof(uint32_t)*2),sizeof(uint32_t));
					if(accept_m == 1)
						std::cout << "nouveau pseudo Ok" << std::endl;
					else
						std::cout << "nouveau pseudo Ko" << std::endl;
				}
			}
			if(FD_ISSET(stdin, &readfds))
			{
				char buff [100];
				memset(buff,0,100);
				//int size=100;
				read(stdin,buff,100);
				std::cout << "read from cin: "<< buff << std::endl;
				buff[strlen(buff)-1] = '\0';
				if(strcmp(buff,"quit")==0)
					quit=true;
				else
				{
					Message* message = new Message(1,buff);
					socket->writeMessage(message);
				}
			}
		}
	}while(quit!=true);

}


