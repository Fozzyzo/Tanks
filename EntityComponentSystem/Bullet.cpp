#include "Bullet.h"


Bullet::Bullet()
{
	m_speed = 3.5f;
	m_rendered_shape = sf::RectangleShape();
	m_rendered_shape.setSize(sf::Vector2f(5, 5));
	m_rendered_shape.setFillColor(sf::Color(0, 0, 0));
	m_rendered_shape.setPosition(sf::Vector2f(-20, 0));
	m_position = m_rendered_shape.getPosition();
	m_bullet_status = false;
}


Bullet::~Bullet()
{
}

void Bullet::Set_Velocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
void Bullet::Set_Position(sf::Vector2f position)
{
	m_position = position;
	m_rendered_shape.setPosition(position);
}
void Bullet::Set_Rotation(float rotation)
{
	m_rendered_shape.setRotation(rotation);
}

void Bullet::Set_Bullet_Status(bool isShot)
{
	m_bullet_status = isShot;
}

sf::Vector2f Bullet::Get_Position()
{
	return m_rendered_shape.getPosition();
}

sf::FloatRect Bullet::Get_Global_Bounds()
{
	return m_rendered_shape.getGlobalBounds();
}
void Bullet::Update(sf::Time delta_time)
{
	if (m_bullet_status)
	{	
		m_position += (m_velocity + (delta_time.asSeconds() * gravity_constant * 0.5f)) * m_speed;
		m_velocity += gravity_constant * delta_time.asSeconds();

		m_rendered_shape.setPosition(m_position);
	}
}

void Bullet::Draw(sf::RenderWindow &window)
{
	if (m_bullet_status)
	{
		window.draw(m_rendered_shape);
	}
}
