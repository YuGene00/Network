#include "server_socket.h"

ServerSocket::ServerSocket() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error");
	}

	_socket = CreateSocket();
}
SOCKET ServerSocket::CreateSocket() {
	SOCKET createdSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (createdSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}

	return createdSocket;
}

ServerSocket::~ServerSocket() {
	closesocket(_socket);
	WSACleanup();
}

void ServerSocket::Bind(char* port) {
	Bind(atoi(port));
}
void ServerSocket::Bind(USHORT port) {
	SOCKADDR_IN serverAddress;
	auto addressSize = sizeof(serverAddress);
	memset(&serverAddress, 0, addressSize);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	if (bind(_socket, (sockaddr*)&serverAddress, addressSize) == SOCKET_ERROR) {
		ErrorHandling("bind() error");
	}
}

void ServerSocket::Listen(int backlog) {
	if (listen(_socket, backlog) == SOCKET_ERROR) {
		ErrorHandling("listen() error");
	}
}

ClientSocket* ServerSocket::Accept() {
	SOCKADDR_IN address;
	int addressSize = sizeof(address);

	SOCKET clientSocket = accept(_socket, (SOCKADDR*)&address, &addressSize);
	if (clientSocket == SOCKET_ERROR) {
		ErrorHandling("accept() error");
	}
	else {
		char addressString[16];
		inet_ntop(AF_INET, &address.sin_addr, addressString, sizeof(addressString));
		printf("Connected client from %s\n", addressString);
	}

	SocketData socketData = SocketData(clientSocket, address);
	return new ClientSocket(socketData);
}

void ServerSocket::ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}