#pragma once

#include <process.h>
#include "SFML\Graphics.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "Player.h"
#include "MechanicHandler.h"
#include "GameServer.h"
#include "GameClient.h"

void Server_Update(void*);
void Client_Update(void);


class Game
{
public:
	Game();
	~Game();
	sf::RenderWindow& GetWindow();
	void StartUp();
	void Update();

private:

	sf::RenderWindow m_window;
	sf::Texture texture;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	sf::Event event;
	Player player1;
	Player player2;
	MechanicHandler mechanicHandler;
};

