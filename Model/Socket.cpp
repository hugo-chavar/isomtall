#include "Socket.h"

#include <iostream>

Socket::Socket(){
	this->setMaxPendingConnections(0);
}

Socket::Socket(unsigned long ip, int port, const int maxPendingConnections){
	this->setSocketFileDescriptor(socket(AF_INET,SOCK_STREAM,0));
	memset((void*)&(this->getAddress()),0,sizeof(this->getAddress()));
	this->getAddress().sin_family = AF_INET;
	this->getAddress().sin_port = htons(static_cast<u_short>(port));
	this->getAddress().sin_addr.s_addr = ip;
	this->setMaxPendingConnections(maxPendingConnections);
}

void Socket::setSocketFileDescriptor(const SOCKET socketFileDescriptor){
	this->socketFileDescriptor = socketFileDescriptor;
}

void Socket::setMaxPendingConnections(const int maxPendingConnections){
	this->maxPendingConnections = maxPendingConnections;
}

const int Socket::bindSocket(){
	return bind(this->getSocketFileDescriptor(),(struct sockaddr*)&(this->getAddress()),sizeof(this->getAddress()));
}

void Socket::listenForConnections(){
	listen(this->getSocketFileDescriptor(),this->getMaxPendingConnections());
}

Socket* Socket::acceptConnection() {
	int addressLength;
	SOCKET aux;

	Socket* newSocket = new Socket();
	addressLength = sizeof(newSocket->getAddress());
	aux = accept(this->getSocketFileDescriptor(),(struct sockaddr*)&(newSocket->getAddress()),&addressLength);
	if (aux != INVALID_SOCKET) {
		newSocket->setSocketFileDescriptor(aux);
		return newSocket;
	} else {
		delete newSocket;
		return NULL;
	}
}

const int Socket::connectTo(){
	return connect(this->getSocketFileDescriptor(),(struct sockaddr*)&(this->getAddress()),sizeof(this->getAddress()));
}

const int Socket::receiveData(char* buffer, int bufferLength){
	memset((void*)buffer,'\0',bufferLength);
	return recv(this->getSocketFileDescriptor(),buffer,bufferLength,0);
}

const int Socket::sendData(const char* buffer){
	return send(this->getSocketFileDescriptor(),buffer,strlen(buffer),0);
}

void Socket::disconect(){
	shutdown(this->getSocketFileDescriptor(),SD_BOTH);
	closesocket(this->getSocketFileDescriptor());
}

SOCKET Socket::getSocketFileDescriptor(){
	return this->socketFileDescriptor;
}

struct sockaddr_in& Socket::getAddress(){
	return this->address;
}

int Socket::getMaxPendingConnections(){
	return this->maxPendingConnections;
}

Socket::~Socket(){
}