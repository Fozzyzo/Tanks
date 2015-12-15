#include "NetworkServices.h"


int NetworkServices::sendMessage(SOCKET socket, char* message, int message_size)
{
	return send(socket, message, message_size, 0);
}

int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
{
	return recv(curSocket, buffer, bufSize, 0);
}
