#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
class GameClient
{
public:
	GameClient(void);
	~GameClient(void);
	void Send_Action_Packets();
	void Update();

	char network_data[MAX_PACKET_SIZE];
	ClientNetwork* network;
};

