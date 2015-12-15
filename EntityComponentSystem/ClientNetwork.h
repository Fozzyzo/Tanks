#pragma once

// Networking libraries
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "NetworkServices.h"
#include "NetworkData.h"


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientNetwork
{
public:
	int results;
	SOCKET connect_socket;
	ClientNetwork(void);
	~ClientNetwork(void);
	int Receive_Packets(char* receive_buffer);
};

