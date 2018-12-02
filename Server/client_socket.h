#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "received_message.h"

typedef struct SocketData {
	SOCKET socket;
	SOCKADDR_IN address;

	SocketData(SOCKET socket, SOCKADDR_IN address) {
		this->socket = socket;
		this->address = address;
	}
} SocketData;

class ClientSocket {

public:
	ClientSocket(SocketData &socketData);
	~ClientSocket();

	ReceivedMessage Receive();

	void Send(ReceivedMessage &message);
	void Send(char* message, int length);

	char* GetAddress();

private:
	SOCKET _socket;
	SOCKADDR_IN _address;
	char _addressString[16];
};

#endif // !CLIENT_SOCKET_H
