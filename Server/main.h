#ifndef MAIN_H
#define MAIN_H

#include <list>

#include "server_socket.h"

class Main
{
public:
	Main();
	int Run(int argc, char *argv[]);

private:
	void RunCalculator();
	int CalculateNumbersByArithmetic();
	int CalculateNumbersByArithmetic(int numberX, int numberY);

	std::list<int> ReceiveNumbers();
	int ReceiveNumberCount();
	char ReceiveArithmetic();
	void AddReceivedMessage(ReceivedMessage message);

private:
	ServerSocket _serverSocket;
	ClientSocket* _clientSocket;

	char _receivedMessage[BUF_SIZE];
	int _receivedLength;

	std::list<int> _numbers;
	char _arithmetic;
};

#endif // !MAIN_H
