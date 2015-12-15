#include "GameClient.h"


GameClient::GameClient(void)
{
	network = new ClientNetwork();

	//packet send init
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.Serialize(packet_data);

	NetworkServices::sendMessage(network->connect_socket, packet_data, packet_size);
}


GameClient::~GameClient(void)
{
}

void GameClient::Send_Action_Packets()
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;
	packet.x = bullet_position.x;
	packet.y = bullet_position.y;
	
	packet.Serialize(packet_data);

	NetworkServices::sendMessage(network->connect_socket, packet_data, packet_size);
}

void GameClient::Update(sf::Vector2f position)
{
	bullet_position = position;
	Packet packet;
	int data_length = network->Receive_Packets(network_data);

	if (data_length <= 0)
	{
		//no data received
		return;
	}

	int i = 0;
	while (i < (unsigned int)data_length)
	{
		packet.Deserialize(&(network_data[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) 
		{

		case ACTION_EVENT:

			//printf("client received action event packet from server\n");

			Send_Action_Packets();

			break;

		default:

			printf("error in packet types\n");

			break;
		}
	}

}
