/*
 * Socket.cpp
 *
 *  Created on: 20 mars 2013
 *      Author: p13amjad
 */

#include "Socket.hh"

Socket::Socket(std::string _host, int _port)
{

	host = _host;
	port_number=_port;

	try
	{
		socket_handler = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	catch(...)
	{std::cerr << "Error socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)" << std::endl; }

	struct sockaddr_in serv_addr;
	/* server IP handler */
	struct hostent * server;

	server = gethostbyname(host.c_str());
	if (server == 0)
	{
		std::cerr << "Error gethostbyname(host)" << std::endl;
	}

	/* C fashion constructor :) */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	/* set IPv4 addressing */
	serv_addr.sin_family = AF_INET;
	/* setup server address */
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	/* set server port number */
	serv_addr.sin_port = htons(port_number);

	/* connect*/
	if(connect(socket_handler, (struct sockaddr *) &serv_addr, sizeof(serv_addr))==-1)
		throw std::runtime_error("Erreur connect(socket_handler, (struct sockaddr *) &serv_addr, sizeof(serv_addr))");
}

Socket::~Socket()
{
	close(socket_handler);
}

int Socket::writeMessage(Message* message)
{
	char* buff = new char[message->getSize()];

	memset(buff,0,message->getSize());

	uint32_t size = message->getSize();
	uint32_t type = message->getType();
	memcpy(buff,&size,sizeof(size));
	memcpy(buff+sizeof(size),&type,sizeof(type));
	memcpy(buff+sizeof(size)+sizeof(type),message->getData().c_str(),message->getData().size()+1);
	int wri = write(socket_handler, buff, size);
	if(wri==-1)
		throw std::runtime_error("Erreur write(socket_handler, buff, size)");
	delete [] buff;
	return wri;
}

int Socket::getSocket() const {
	return socket_handler;
}
