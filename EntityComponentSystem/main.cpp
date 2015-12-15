#include <iostream>
#include "SFML\Graphics.hpp"
#include "Game.h"


void Server_Update(void*);

GameServer* server;

int main()
{
	int input;
	std::cout << "Select network setting:\n1) Host server\n2) Join server" << std::endl;
	std::cin >> input;

	switch (input)
	{

	case 1:
		std::cout << "Starting server..." << std::endl;
		
		server = new GameServer();
		_beginthread(Server_Update, 0, (void*)12);
		break;

	case 2:

		std::cout << "Joining server..." << std::endl;
		
		break;

	default:

		std::cout << "Unknown input!" << std::endl;
		break;
	}

	Game game;
	game.StartUp();	
	game.Update();

	return 0;
}

void Server_Update(void* arg)
{
	while (true)
	{
		server->Update();
	}
}


