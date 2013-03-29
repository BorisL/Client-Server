/*
 * Message.hh
 *
 *  Created on: 20 mars 2013
 *      Author: p13amjad
 */

#ifndef MESSAGE_HH_
#define MESSAGE_HH_

#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <string.h>

class Message {
	uint32_t type;
	uint32_t size; //taille en octet du message (header+data)
	std::string data;
	int refreshSize();
public:
	/*
	 *  1: message texte
	 *  2: change nickname
	 *  4: accept nickname
	 *  0xff: ping
	 */
	enum type_message {};
	Message();
	Message(uint32_t, std::string);
	Message(char*);
	virtual ~Message();
	const std::string& getData() const;
	void setData(const std::string&);
	uint32_t getSize() const;
	uint32_t getType() const;
	void setType(uint32_t type);
	char* toChar();

};

#endif /* MESSAGE_HH_ */
