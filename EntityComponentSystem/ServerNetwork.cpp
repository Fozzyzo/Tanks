
#include "ServerNetwork.h"

ServerNetwork::ServerNetwork(void)
{
	WSAData wsa_data;

	listen_socket = INVALID_SOCKET;
	client_socket = INVALID_SOCKET;

	// address info for the server to listen to
	struct addrinfo *result = NULL;
	struct addrinfo si_other;

	// Initialize Winsock
	error = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (error != 0)
	{
		printf("WSAStartup failed with error: %d\n", error);
		exit(1);
	}

	// set address information
	ZeroMemory(&si_other, sizeof(si_other));
	si_other.ai_family = AF_INET;
	si_other.ai_socktype = SOCK_STREAM;
	si_other.ai_protocol = IPPROTO_TCP;
	si_other.ai_flags = AI_PASSIVE;

	//Resolve ip and port
	error = getaddrinfo(NULL, DEFAULT_PORT, &si_other, &result);

	if (error != 0)
	{
		printf("getaddrinfo failed with error : %d", error);
		WSACleanup();
		exit(1);
	}

	listen_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (listen_socket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}

	// Set the mode of the socket to be nonblocking
	u_long iMode = 1;
	error = ioctlsocket(listen_socket, FIONBIO, &iMode);

	if (error == SOCKET_ERROR) 
	{
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(listen_socket);
		WSACleanup();
		exit(1);
	}

	// Setup the TCP listening socket
	error = bind(listen_socket, result->ai_addr, (int)result->ai_addrlen);

	if (error == SOCKET_ERROR) 
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(listen_socket);
		WSACleanup();
		exit(1);
	}

	// no longer need address information
	freeaddrinfo(result);

	// start listening for new clients attempting to connect
	error = listen(listen_socket, SOMAXCONN);

	if (error == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(listen_socket);
		WSACleanup();
		exit(1);
	}
}


ServerNetwork::~ServerNetwork(void)
{
}

// accept new connections
bool ServerNetwork::Accept_New_Client(unsigned int& id)
{
	// if client waiting, accept the connection and save the socket
	client_socket = accept(listen_socket, NULL, NULL);

	if (client_socket != INVALID_SOCKET)
	{
		//disable nagle on the client's socket
		char value = 1;
		setsockopt(client_socket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

		// insert new client into session id table
		sessions.insert(pair<unsigned int, SOCKET>(id, client_socket));

		return true;
	}

	return false;
}

int ServerNetwork::Receive_Data(unsigned int client_id, char* receive_buffer)
{
	if (sessions.find(client_id) != sessions.end())
	{
		SOCKET current_socket = sessions[client_id];
		error = NetworkServices::receiveMessage(current_socket, receive_buffer, MAX_PACKET_SIZE);
		
		if (error == 0)
		{
			printf("connection closed\n");
		}

		return error;
	}

	return 0;
}

void ServerNetwork::Send_All_Clients(char* packets, int total_size)
{
	SOCKET current_socket;
	std::map<unsigned int, SOCKET>::iterator it;
	int send_error;

	for (it = sessions.begin(); it != sessions.end(); it++)
	{
		current_socket = it->second;
		send_error = NetworkServices::sendMessage(current_socket, packets, total_size);
		
		if (send_error = SOCKET_ERROR)
		{
			printf("send failed with error: %d", WSAGetLastError());
			closesocket(current_socket);
		}
	}
}
