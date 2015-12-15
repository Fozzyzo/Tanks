#pragma once

#include <string.h>

#define MAX_PACKET_SIZE 100000

enum Packet_Types
{
	INIT_CONNECTION,
	ACTION_EVENT
};

struct Packet
{
	unsigned int packet_type;
	float x;
	float y;

	void Serialize(char* data)
	{
		memcpy(data, this, sizeof(Packet));
	}

	void Deserialize(char* data)
	{
		memcpy(this, data, sizeof(Packet));
	}
};
