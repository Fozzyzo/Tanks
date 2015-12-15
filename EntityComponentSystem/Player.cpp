#include "Player.h"

Player::Player()
{
}

Player::Player(sf::Vector2f position, sf::Texture& texture)
{
	m_player_name = "";
	m_playerSprite.setPosition(position);
	m_playerSprite.setTexture(texture);
	m_cannon = sf::RectangleShape(sf::Vector2f(20, 3));
	m_cannon.setPosition(position.x + 16, position.y + 16);
	m_cannon.setRotation(-90.0f);
	m_cannon.setFillColor(sf::Color(0, 0, 0));
	m_cannon.setOutlineColor(sf::Color(0, 0, 0));
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_cannon);
	window.draw(m_playerSprite);
}

sf::FloatRect Player::Get_Global_Bounds()
{
	return m_playerSprite.getGlobalBounds();
}

sf::Vector2i Player::Get_Mouse_Position(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

sf::Vector2f Player::Get_Position()
{
	return m_playerSprite.getPosition();
}

sf::Vector2f Player::Get_Center_Position()
{
	return m_playerSprite.getPosition() + sf::Vector2f(16, 16);
}

sf::Vector2f Player::Get_Size()
{
	return sf::Vector2f(32, 32);
}

std::string Player::Get_Player_Name()
{
	return m_player_name;
}

void Player::Set_Cannon_Rotation(float rotation)
{
	m_cannon.setRotation(rotation);
}

void Player::Set_Player_Name(std::string name)
{
	m_player_name = name;
}
bool Player::Get_Mouse_Click()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	else
		return false;
}


