#pragma once
#include "ServerNetwork.h"
class GameServer
{
public:
	GameServer(void);
	~GameServer(void);
	void Receive_From_Clients();
	void Send_Action_Packets();
	void Update();

private:

	static unsigned int client_id;
	char network_data[MAX_PACKET_SIZE];
	ServerNetwork* network;
};

