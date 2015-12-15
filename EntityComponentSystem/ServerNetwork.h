#pragma once

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <map>
#include "NetworkServices.h"
#include "stdafx.h" 
#include "NetworkData.h"

using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881" 

class ServerNetwork
{
public:
	ServerNetwork(void);
	~ServerNetwork(void);
	bool Accept_New_Client(unsigned int& id);
	int Receive_Data(unsigned int client_id, char* receive_buffer);
	void Send_All_Clients(char* packets, int total_size);
	
	SOCKET listen_socket;
	SOCKET client_socket;

	int error;

	std::map<unsigned int, SOCKET> sessions;
};

