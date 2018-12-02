#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "client_socket.h"

class ServerSocket {
public:
	ServerSocket();
	~ServerSocket();

	void Bind(char* port);
	void Bind(USHORT port);
	void Listen(int backlog);
	ClientSocket* Accept();

private:
	SOCKET CreateSocket();
	void ErrorHandling(const char *message);

private:
	SOCKET _socket;
};

#endif // !SERVER_SOCKET_H
