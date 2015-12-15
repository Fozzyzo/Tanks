#pragma once
#include "ServerNetwork.h"
#include "SFML\System\Clock.hpp"
#include "SFML\System\Time.hpp"
class GameServer
{
public:
	GameServer(void);
	~GameServer(void);
	void Receive_From_Clients();
	void Send_Action_Packets();
	void Update();

private:

	sf::Time general_timer;
	sf::Time log_timer;
	int time;
	static unsigned int client_id;
	char network_data[MAX_PACKET_SIZE];
	ServerNetwork* network;
};

