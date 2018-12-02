#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "..\Server\received_message.h"

constexpr int BUF_SIZE_FOR_STRING = BUF_SIZE - 1;

class ClientSocket
{
public:
	ClientSocket();
	~ClientSocket();

	void Connect(char* address, char* port);
	void Connect(ULONG address, USHORT port);

	void Send(char* message, int length);
	ReceivedMessage Recieve();

private:
	SOCKET CreateSocket();
	void ErrorHandling(const char* message);

private:
	SOCKET _socket;

};

#endif // !CLIENT_SOCKET_H
