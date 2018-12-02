#include "client_socket.h"

ClientSocket::ClientSocket(SocketData &socketData) {
	_socket = socketData.socket;
	_address = socketData.address;
	inet_ntop(AF_INET, &_address.sin_addr, _addressString, sizeof(_addressString));
}

ClientSocket::~ClientSocket() {
	closesocket(_socket);
}

ReceivedMessage ClientSocket::Receive() {
	ReceivedMessage message = ReceivedMessage();
	message .length = recv(_socket, message.message, BUF_SIZE, 0);
	return message;
}

void ClientSocket::Send(ReceivedMessage &message) {
	Send(message.message, message.length);
}
void ClientSocket::Send(char* message, int length) {
	send(_socket, message, length, 0);
}

char * ClientSocket::GetAddress()
{
	return _addressString;
}
