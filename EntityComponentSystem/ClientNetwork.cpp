#include "ClientNetwork.h"


ClientNetwork::ClientNetwork(void)
{
	WSADATA wsaData;

	connect_socket = INVALID_SOCKET;

	struct addrinfo *result = NULL,
					*ptr = NULL, 
					si_other;

	//Init winsock
	results = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (results != 0)
	{
		printf("WSAStartUp failed with error code: %d", result);
		exit(0);
	}

	//setup address
	ZeroMemory(&si_other, sizeof(si_other));
	si_other.ai_family = AF_UNSPEC;
	si_other.ai_socktype = SOCK_STREAM;
	si_other.ai_protocol = IPPROTO_TCP;

	
	//resolve ip and port
	results = getaddrinfo("127.0.0.1", DEFAULT_PORT, &si_other, &result);

	if (results != 0)
	{
		printf("getaddrinfo failed with error: %d\n", results);
		WSACleanup();
		exit(1);
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{
		// Create a SOCKET for connecting to server
		connect_socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (connect_socket == INVALID_SOCKET) 
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}

		// Connect to server.
		results = connect(connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (results == SOCKET_ERROR)
		{
			closesocket(connect_socket);
			connect_socket = INVALID_SOCKET;
			printf("The server is down... did not connect\n");
		}
	}

	freeaddrinfo(result);

	if (connect_socket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		exit(1);
	}

	u_long i_mode = 1;

	results = ioctlsocket(connect_socket, FIONBIO, &i_mode);

	if (results == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error code : %d\n", results);
		closesocket(connect_socket);
		WSACleanup();
		exit(1);
	}

	char value = 1;

	setsockopt(connect_socket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}

ClientNetwork::~ClientNetwork(void)
{
}

int ClientNetwork::Receive_Packets(char* receive_buffer)
{
	results = NetworkServices::receiveMessage(connect_socket, receive_buffer, MAX_PACKET_SIZE);

	if (results == 0)
	{
		printf("Connection closed");
		closesocket(connect_socket);
		WSACleanup();
		exit(1);
	}

	return results;
}
