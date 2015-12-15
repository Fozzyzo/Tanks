#include <string>
#include <iostream>
#include <math.h>
#include "MechanicHandler.h"

MechanicHandler::MechanicHandler()
{ 
	timer = 0.0f;
	cooldown = 0;
	bullet = Bullet();
	game_state = GameState::PAUSED;
}


MechanicHandler::~MechanicHandler()
{
}

void MechanicHandler::Update(Player& player1, Player& player2, sf::RenderWindow& window, sf::Time delta_time)
{

	sf::Vector2f bullet_velocity;

	cooldown += delta_time.asSeconds();

	sf::Vector2f d_position = sf::Vector2f(0, 0);
	float rotation = 0.0f;

	switch(game_state)
	{
	case GameState::PAUSED:

		game_state = GameState::PLAYER1_AIMING;
		std::cout << player1.Get_Player_Name() << "'s turn" << std::endl;
		break;

	case GameState::PLAYER1_AIMING:
	
		d_position = sf::Vector2f(player1.Get_Mouse_Position(window).x - player1.Get_Center_Position().x, player1.Get_Mouse_Position(window).y - player1.Get_Center_Position().y);
		rotation = atan2f(d_position.x, d_position.y) * 180 / PI + 270;
		player1.Set_Cannon_Rotation(-rotation);

		if (player1.Get_Mouse_Click())
		{	
			bullet_velocity = Normalize_Vector(sf::Vector2f(player1.Get_Mouse_Position(window).x, player1.Get_Mouse_Position(window).y) - player1.Get_Position());

			bullet.Set_Position(player1.Get_Center_Position());
			bullet.Set_Velocity(bullet_velocity);
			bullet.Set_Bullet_Status(true);
			game_state = GameState::PLAYER1_SHOT;
			
			std::cout << player1.Get_Player_Name() <<" shot a bullet! " << std::endl;
		}

		break;

	case GameState::PLAYER1_SHOT:
		
		timer += delta_time.asSeconds();
		Collision_Check(player2);
		if (timer > 8)
		{
			timer += delta_time.asSeconds();
			cooldown += delta_time.asSeconds();

			std::cout << player2.Get_Player_Name() << "'s turn" << std::endl;
			game_state = GameState::PLAYER2_AIMING;
			bullet.Set_Bullet_Status(false);
			timer = 0;
		}
		break;

	case GameState::PLAYER2_AIMING:

		d_position = sf::Vector2f(player2.Get_Mouse_Position(window).x - player2.Get_Center_Position().x, player2.Get_Mouse_Position(window).y - player2.Get_Center_Position().y);
		rotation = atan2f(d_position.x, d_position.y) * 180 / PI + 270;
		player2.Set_Cannon_Rotation(-rotation);

		if (player2.Get_Mouse_Click())
		{
			std::cout << player2.Get_Player_Name() << " shot a bullet! " << std::endl;
			bullet_velocity = Normalize_Vector(sf::Vector2f(player2.Get_Mouse_Position(window).x, player2.Get_Mouse_Position(window).y) - player2.Get_Center_Position());
			bullet.Set_Position(player2.Get_Center_Position());
			bullet.Set_Velocity(bullet_velocity);
			bullet.Set_Bullet_Status(true);
			game_state = GameState::PLAYER2_SHOT;
			
		}
		
		break;

	case GameState::PLAYER2_SHOT:

		timer += delta_time.asSeconds();
		Collision_Check(player1);

		if (timer > 8)
		{
			std::cout << player1.Get_Player_Name() <<"'s turn" << std::endl;
			game_state = GameState::PLAYER1_AIMING;
			bullet.Set_Bullet_Status(false);
			timer = 0;
		}

		break;
	}

	bullet.Update(delta_time);
	bullet.Draw(window);

	if (cooldown > 1)
	{
		std::cout << "Bullets pos x = " << bullet.Get_Position().x << ", y = " << bullet.Get_Position().y << std::endl;
		cooldown = 0;
	}
}

sf::Vector2f MechanicHandler::Normalize_Vector(sf::Vector2f vector)
{
	float length;
	sf::Vector2f normalized_vec2;

	length = sqrt(vector.x * vector.x + vector.y * vector.y);

	if (length != 0)
	{
		normalized_vec2 = sf::Vector2f(vector.x / length, vector.y / length);
	}

	return normalized_vec2;
}

bool MechanicHandler::Collision_Check(Player& player)
{
	if (player.Get_Global_Bounds().intersects(bullet.Get_Global_Bounds()))
	{
		bullet.Set_Bullet_Status(false);
		bullet.Set_Position(sf::Vector2f(0, 0));
		std::cout << player.Get_Player_Name() << " was hit!" << std::endl;
		return true;
	}

	else
		return false;
}
