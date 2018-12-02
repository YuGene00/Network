#include "main.h"

int main(int argc, char *argv[]) {
	Main main = Main();
	return main.Run(argc, argv);
}

Main::Main() :_numbers(std::list<int>()) {}

int Main::Run(int argc, char *argv[]) {
	if (argc != 2) {
		printf_s("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	_serverSocket = ServerSocket();
	_serverSocket.Bind(argv[1]);
	_serverSocket.Listen(5);

	for (int i = 0, max = 5; i < max; ++i) {
		_clientSocket = _serverSocket.Accept();

		try {
			RunCalculator();
		}
		catch (int exception) {
			printf_s("Disconnected from %s!!\n", _clientSocket->GetAddress());
		}

		delete _clientSocket;
	}

	return 0;
}

void Main::RunCalculator()
{
	_receivedLength = 0;
	ReceivedMessage message = _clientSocket->Receive();
	while (!message.IsEmpty()) {
		AddReceivedMessage(message);

		_numbers = ReceiveNumbers();
		_arithmetic = ReceiveArithmetic();
		int result = CalculateNumbersByArithmetic();

		char sendMessage[sizeof(int)];
		memcpy_s(sendMessage, sizeof(int), &result, sizeof(int));
		_clientSocket->Send(sendMessage, sizeof(int));

		message = _clientSocket->Receive();
	}
}

int Main::CalculateNumbersByArithmetic()
{
	int result = *_numbers.begin();
	if (_numbers.size == 1)
		return result;

	for (auto itr = ++_numbers.begin(); itr != _numbers.end(); ++itr) {
		result = CalculateNumbersByArithmetic(result, *itr);
	}
	return result;
}

int Main::CalculateNumbersByArithmetic(int numberX, int numberY)
{
	switch (_arithmetic)
	{
	case '+':
		return numberX + numberY;
	case '-':
		return numberX - numberY;
	case '*':
		return numberX * numberY;
	case '/':
		return numberY != 0 ? numberX / numberY : numberX;
	default:
		return numberX;
	}
}

std::list<int> Main::ReceiveNumbers()
{
	int count = ReceiveNumberCount();
	int totalLength = (count + 1) * sizeof(int);
	while (_receivedLength < totalLength) {
		ReceivedMessage message = _clientSocket->Receive();
		if (message.IsEmpty())
			throw (-1);

		AddReceivedMessage(message);
	}

	_numbers.clear();
	while (_numbers.size < count) {
		int number = 0;
		memcpy_s(&number, sizeof(int), _receivedMessage + (_numbers.size + 1) * sizeof(int), sizeof(int));
		_numbers.push_back(number);
	}
	return _numbers;
}

int Main::ReceiveNumberCount()
{
	while (_receivedLength < sizeof(int)) {
		ReceivedMessage message = _clientSocket->Receive();
		if (message.IsEmpty())
			throw (-1);

		AddReceivedMessage(message);
	}

	int receivedResult = 0;
	memcpy_s(&receivedResult, sizeof(int), _receivedMessage, sizeof(int));
	return receivedResult;
}

char Main::ReceiveArithmetic()
{
	int totalLength = (_numbers.size + 1) * sizeof(int) + sizeof(char);
	while (_receivedLength < totalLength) {
		ReceivedMessage message = _clientSocket->Receive();
		if (message.IsEmpty())
			throw (-1);

		AddReceivedMessage(message);
	}

	return _receivedMessage[totalLength - 1];
}

void Main::AddReceivedMessage(ReceivedMessage message)
{
	if (message.IsEmpty())
		return;

	memcpy_s(_receivedMessage + _receivedLength, BUF_SIZE - _receivedLength, message.message, message.length);
	_receivedLength += message.length;
}
