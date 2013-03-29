/*
 * Message.cpp
 *
 *  Created on: 20 mars 2013
 *      Author: p13amjad
 */

#include "Message.hh"

Message::Message()
{
	type=-1;
	data='\0';
	refreshSize();

}

Message::Message(uint32_t _type, std::string _data)
{
	type=_type;
	data=_data;
	refreshSize();
}

Message::~Message()
{}

const std::string& Message::getData() const
{
	return data;
}

void Message::setData(const std::string& data)
{
	this->data = data;
}

uint32_t Message::getSize() const
{
	return size;
}

uint32_t Message::getType() const
{
	return type;
}

void Message::setType(uint32_t type)
{
	this->type = type;
}

int Message::refreshSize()
{
	size=sizeof(type) + sizeof(size)+ data.size()+1;
	return size;
}

Message::Message(char* buff)
{
	std::string buff_s(buff);
	type=atoi((buff_s.substr(0,sizeof(int32_t)-1)).c_str());
	std::cout << type << " " << sizeof(uint32_t) << std::endl;
	size=atoi((buff_s.substr(sizeof(int32_t),sizeof(int32_t)*2-1)).c_str());
	std::cout << size << std::endl;
	data=buff_s.substr(sizeof(int32_t)*2,size-1);
	std::cout << data << std::endl;
}

char* Message::toChar()
{
	char* buff = new char[getSize()];
	memset(buff,0,getSize());
	memcpy(buff,&size,sizeof(uint32_t));
	memcpy(buff+sizeof(uint32_t),&type,sizeof(uint32_t));
	memcpy(buff+2*sizeof(uint32_t),data.c_str(),data.length()+1);
	return buff;
}
