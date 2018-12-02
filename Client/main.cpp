#include "main.h"

int main(int argc, char *argv[]) {
	Main main = Main();
	return main.Run(argc, argv);
}

Main::Main() :_numbers(std::list<int>()) {}

int Main::Run(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	_clientSocket = ClientSocket();
	_clientSocket.Connect(argv[1], argv[2]);

	char* message = GetInputMessage();
	while (!IsQuit(message)) {
		RunCalculator(message);
		message = GetInputMessage();
	}

	return 0;
}

char* Main::GetInputMessage() {
	fputs("Input message(Q to quit): ", stdout);
	fgets(_inputMessage, BUF_SIZE_FOR_STRING, stdin);
	return _inputMessage;
}

void Main::RunCalculator(char* message)
{
	StringToNumberConverter converter = StringToNumberConverter();
	ConvertedNumber number = converter.Convert(message);

	if (number.isNumber) {
		_numbers.push_back(number);
	}
	else if (IsArithmetic(message[0])) {
		_arithmetic = message[0];
		RunCalculatorByServer();
		_numbers.clear();
	}
}

bool Main::IsQuit(char* message) {
	return strcmp(message, "q\n") == 0 || strcmp(message, "Q\n") == 0;
}

bool Main::IsArithmetic(char character)
{
	return character == '+' || character == '-' || character == '*' || character == '/';
}

void Main::RunCalculatorByServer()
{
	SendToServer();
	printf("Message from server: %d", ReceiveFromServer());
}

void Main::SendToServer()
{
	if (_numbers.size <= 1)
	{
		fputs("Input more than two numbers before inputting arithmetic\n", stdout);
		return;
	}

	char* sendMessage = GetSendMessage();
	_clientSocket.Send(sendMessage, BUF_SIZE);
}

char* Main::GetSendMessage()
{
	memset(_sendMessage, 0, BUF_SIZE);

	memcpy_s(_sendMessage, BUF_SIZE, &_numbers.size, sizeof(int));

	int writedLength = sizeof(int);
	for (auto itr = _numbers.begin(); itr != _numbers.end() && writedLength < BUF_SIZE - 1; ++itr, writedLength += sizeof(int)) {
		memcpy_s(_sendMessage + writedLength, BUF_SIZE - writedLength, &*itr, sizeof(int));
	}

	_sendMessage[min(writedLength + 1, BUF_SIZE - 1)] = _arithmetic;

	return _sendMessage;
}

int Main::ReceiveFromServer()
{
	char receivedMessage[BUF_SIZE];
	int receivedLength = 0;

	while (receivedLength < sizeof(int)) {
		ReceivedMessage message = _clientSocket.Recieve();
		memcpy_s(receivedMessage + receivedLength, BUF_SIZE - receivedLength, message.message, message.length);
		receivedLength += message.length;
	}

	int receivedResult = 0;
	memcpy_s(&receivedResult, sizeof(int), receivedMessage, sizeof(int));
	return receivedResult;
}
