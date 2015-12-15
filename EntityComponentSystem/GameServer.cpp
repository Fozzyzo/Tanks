#include "GameServer.h"
#include "SFML\System\Vector2.hpp"

unsigned int GameServer::client_id;

GameServer::GameServer(void)
{
	client_id = 0;

	network = new ServerNetwork();
}


GameServer::~GameServer()
{
}

void GameServer::Send_Action_Packets()
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.Serialize(packet_data);

	network->Send_All_Clients(packet_data, packet_size);
}

void GameServer::Receive_From_Clients()
{
	sf::Clock clock;
	sf::Time log_timer;
	Packet packet;
	
	std::map<unsigned int, SOCKET>::iterator it;

	general_timer = clock.getElapsedTime();
	log_timer += clock.getElapsedTime();
	clock.restart();

	for (it = network->sessions.begin(); it != network->sessions.end(); it++)
	{
		int data_length = network->Receive_Data(it->first, network_data);

		if (data_length <= 0)
		{
			continue;
		}

		int i = 0;

		while (i < (unsigned)data_length)
		{
			packet.Deserialize(&(network_data[i]));
			i += sizeof(Packet);

			switch (packet.packet_type)
			{
				case INIT_CONNECTION:

					printf("server received init packet from client\n");
					Send_Action_Packets();
					break;

				case ACTION_EVENT:

					if (log_timer.asSeconds() > 4)
					{
						printf("server received action packet from client\n");
						printf("Bullet position: x = %f.2, y = %f.2", packet.x, packet.y);
					}

					Send_Action_Packets();
					break;

				default:

					printf("Unknown packet type\n");
					break;
			}
		}
	}
}

void GameServer::Update()
{
	if (network->Accept_New_Client(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);
		client_id++;
	}

	Receive_From_Clients();
}
