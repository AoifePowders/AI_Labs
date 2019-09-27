#include "Character.h"

void Character::update()
{
	move();
	boundary();
	rotate();
}

void Character::setUp(sf::Texture &t_texture, sf::Vector2f& t_position, sf::Vector2f& t_scale)
{
	m_position = t_position;
	characterSprite.setPosition(m_position);
	characterSprite.setScale(t_scale);
	characterSprite.setTexture(t_texture);
	characterSprite.setOrigin(characterSprite.getTexture()->getSize().x / 2,characterSprite.getTexture()->getSize().y / 2);
}

//move by changing the position with velocity
void Character::move()
{
	m_radians = (m_rotationSpeed - 90) * (3.14159 / 180);
	m_direction = { cos(m_radians), sin(m_radians) };

	m_magnitude = sqrt((m_direction.x * m_direction.x) + (m_direction.y * m_direction.y));
	m_direction.x = m_direction.x * (1 / m_magnitude);
	m_direction.y = m_direction.y * (1 / m_magnitude);

	float actualspeed = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));

	if (actualspeed > maxSpeed)
	{
		m_velocity *= maxSpeed / actualspeed;
	}
	characterSprite.setRotation(m_rotation);

	m_velocity += m_direction * m_acceleration;
	m_position += m_velocity;
	characterSprite.setPosition(m_position);
}

//wrap around
void Character::boundary()
{
	if (characterSprite.getPosition().x <= 0)
	{
		m_position = sf::Vector2f(1019, characterSprite.getPosition().y);
		characterSprite.setPosition(m_position);
	}
	else if (characterSprite.getPosition().x >= 1020)
	{
		m_position = sf::Vector2f(1, characterSprite.getPosition().y);
		characterSprite.setPosition(m_position);
	}

	if (characterSprite.getPosition().y <= 0)
	{
		m_position = sf::Vector2f(characterSprite.getPosition().x, 1019);
		characterSprite.setPosition(m_position);
	}
	else if (characterSprite.getPosition().y >= 1020)
	{
		m_position = sf::Vector2f(characterSprite.getPosition().x, 1);
		characterSprite.setPosition(m_position);
	}
}

//rotate character
void Character::rotate()
{
	characterSprite.setRotation(m_rotationSpeed);
}

void Character::render(sf::RenderWindow& t_window)
{
	t_window.draw(characterSprite);
}
