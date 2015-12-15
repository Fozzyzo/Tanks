#include "Game.h"
#include "SFML\System.hpp"

GameClient* client;

Game::Game() : m_window(sf::VideoMode(800, 600), "SFML window")
{
}

Game::~Game()
{
}

sf::RenderWindow& Game::GetWindow()
{
	return m_window;
}

void Game::StartUp()
{
	texture.loadFromFile("TankBottom.png");

	sprite1.setTexture(texture);
	sprite2.setTexture(texture);

	player1 = Player(sf::Vector2f(100, 500), texture);
	player2 = Player(sf::Vector2f(700, 500), texture);
}

void Game::Update()
{
	client = new GameClient;
	sf::Clock clock;
	sf::Time delta_time;
	m_window.setFramerateLimit(60);

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		client->Update();
		delta_time = clock.getElapsedTime();

		clock.restart();
		//Game state updating
		m_window.clear(sf::Color(255, 255, 255));
		player1.Set_Player_Name("Tappokone");
		player2.Set_Player_Name("Juoppo");
		mechanicHandler.Update(player1, player2, m_window, delta_time);

		//Drawing functions
		
		player1.Draw(m_window);
		player2.Draw(m_window);
		m_window.display();
	
	}
}