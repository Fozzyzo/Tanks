#pragma once
#include "Player.h"
#include "Bullet.h"

#define PI 3.14159265359

class MechanicHandler
{
	enum GameState
	{
		PAUSED,
		PLAYER1_AIMING,
		PLAYER1_SHOT,
		PLAYER2_AIMING,
		PLAYER2_SHOT
	};

public:
	MechanicHandler();
	~MechanicHandler();
	void Update(Player& player1, Player& player2, sf::RenderWindow& window, sf::Time delta_time);
	bool Collision_Check(Player& player);
	sf::Vector2f Normalize_Vector(sf::Vector2f vector);
	
private:

	Bullet bullet;
	GameState game_state;
	float cooldown;
	float timer;
};

