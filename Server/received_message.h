#ifndef RECEIVED_MESSAGE_H
#define RECEIVED_MESSAGE_H

constexpr int BUF_SIZE = 1024;

typedef struct ReceivedMessage {
	char message[BUF_SIZE];
	int length;

	bool IsEmpty() {
		return length <= 0;
	}
} ReceivedMessage;

#endif // !RECEIVED_MESSAGE_H
