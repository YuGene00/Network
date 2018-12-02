#include "client_socket.h"

ClientSocket::ClientSocket() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error");
	}

	_socket = CreateSocket();
}
SOCKET ClientSocket::CreateSocket() {
	SOCKET createdSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (createdSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}
	
	return createdSocket;
}

ClientSocket::~ClientSocket() {
	closesocket(_socket);
	WSACleanup();
}

void ClientSocket::Connect(char* address, char* port) {
	IN_ADDR inAddr;
	inet_pton(AF_INET, address, &inAddr);
	ULONG convertedAddress = ntohl(inAddr.s_addr);

	USHORT convertedPort = atoi(port);
	Connect(convertedAddress, convertedPort);
}
void ClientSocket::Connect(ULONG address, USHORT port) {
	SOCKADDR_IN serverAddress;
	auto addressSize = sizeof(serverAddress);
	memset(&serverAddress, 0, addressSize);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(address);
	serverAddress.sin_port = htons(port);

	if (connect(_socket, (SOCKADDR*)&serverAddress, addressSize) == SOCKET_ERROR) {
		ErrorHandling("connect() error");
	}
	else {
		puts("Connected..........");
	}
}

void ClientSocket::Send(char* message, int length) {
	send(_socket, message, length, 0);
}

ReceivedMessage ClientSocket::Recieve() {
	ReceivedMessage message = ReceivedMessage();
	message.length = recv(_socket, message.message, BUF_SIZE_FOR_STRING, 0);
	message.message[message.length] = 0;
	return message;
}

void ClientSocket::ErrorHandling(const char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}