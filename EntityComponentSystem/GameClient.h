#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "SFML\System\Vector2.hpp"
class GameClient
{
public:
	GameClient(void);
	~GameClient(void);
	void Send_Action_Packets();
	void Update(sf::Vector2f position);

	char network_data[MAX_PACKET_SIZE];
	ClientNetwork* network;

private:
	sf::Vector2f bullet_position;
};

