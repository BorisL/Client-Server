/*
 * Socket.hh
 *
 *  Created on: 20 mars 2013
 *      Author: p13amjad
 */

#ifndef SOCKET_HH_
#define SOCKET_HH_
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdexcept>

#include "Message.hh"

class Socket {
	int socket_handler;
	std::string host;
	int port_number;
public:
	Socket(std::string, int);
	virtual ~Socket();
	int writeMessage(Message*);
	int getSocket() const;
};

#endif /* SOCKET_HH_ */
