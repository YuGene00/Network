#ifndef MAIN_H
#define MAIN_H

#include <list>

#include "client_socket.h"
#include "string_to_number_converter.h"

class Main
{
public:
	Main();
	int Run(int argc, char *argv[]);

private:
	char* GetInputMessage();

	void RunCalculator(char* message);

	bool IsQuit(char* message);
	bool IsArithmetic(char character);

	void RunCalculatorByServer();
	void SendToServer();
	char* GetSendMessage();

	int ReceiveFromServer();

private:
	ClientSocket _clientSocket;

	char _inputMessage[BUF_SIZE];
	char _sendMessage[BUF_SIZE];

	std::list<int> _numbers;
	char _arithmetic;
};

#endif // !MAIN_H
