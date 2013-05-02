#ifndef _SOCKET_H_
#define _SOCKET_H_


#include <sys/types.h>
#include <winsock2.h>

class Socket{
private:
	SOCKET socketFileDescriptor;

	struct sockaddr_in address;

	int maxPendingConnections;

	void setSocketFileDescriptor(const SOCKET socketFileDescriptor);

	void setMaxPendingConnections(const int maxPendingConnections);

	Socket();

	SOCKET getSocketFileDescriptor();

	int getMaxPendingConnections();

	struct sockaddr_in& getAddress();

public:
	Socket(unsigned long ip, int port, const int maxPendingConnections);

	const int bindSocket();

	void listenForConnections();

	Socket* acceptConnection();

	const int connectTo();

	const int receiveData(char* buffer, int bufferLength);

	const int sendData(const char* buffer);

	void disconect();

	~Socket();
};

#endif // _SOCKET_H_
