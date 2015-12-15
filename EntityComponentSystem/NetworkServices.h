#pragma once
#include <WinSock2.h>
#include <Windows.h>
class NetworkServices
{
public:
	
	static int sendMessage(SOCKET socket, char* message, int message_size);
	static int receiveMessage(SOCKET socket, char* buffer, int bufSize);
};

