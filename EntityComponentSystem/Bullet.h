#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"

#define gravity_constant sf::Vector2f(0, 0.3f)

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Set_Velocity(sf::Vector2f velocity);
	void Set_Position(sf::Vector2f position);
	void Set_Rotation(float rotation);
	void Set_Bullet_Status(bool isShot);
	void Update(sf::Time delta_time);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f Get_Position();
	sf::FloatRect Get_Global_Bounds();

public:
	
	bool m_bullet_status;
	float m_speed;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::RectangleShape m_rendered_shape;

};

