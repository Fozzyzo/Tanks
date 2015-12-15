#pragma once

#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window\Mouse.hpp"

class Player
{
public:
	Player();
	Player(sf::Vector2f position, sf::Texture& texture);
	~Player();
	void Draw(sf::RenderWindow& window);
	sf::Vector2i Get_Mouse_Position(sf::RenderWindow& window);
	sf::Vector2f Get_Position();
	sf::Vector2f Get_Center_Position();
	sf::Vector2f Get_Size();
	sf::FloatRect Get_Global_Bounds();
	std::string Get_Player_Name();
	void Set_Cannon_Rotation(float rotation);
	void Set_Player_Name(std::string name);
	bool Get_Mouse_Click();

private:
	
	std::string m_player_name;
	sf::Texture m_texture;
	sf::Sprite m_playerSprite;
	sf::RectangleShape m_cannon;
};

