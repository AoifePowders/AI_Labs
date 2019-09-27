#include "AI.h"

AI::AI()
{
}

AI::~AI()
{
}

void AI::setUp(sf::Texture& t_aiTexture, sf::Vector2f& t_position, sf::Vector2f& t_scale)
{
	m_position = t_position;
	m_aiSprite.setPosition(m_position);
	m_aiSprite.setRotation(m_rotation);
	m_aiSprite.setTexture(t_aiTexture);
	m_aiSprite.setOrigin(m_aiSprite.getTexture()->getSize().x / 2, m_aiSprite.getTexture()->getSize().y / 2);
	m_aiSprite.setScale(t_scale);
	srand(time(0));
}

void AI::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_aiSprite);
}

void AI::boundary()
{
	if (m_aiSprite.getPosition().x <= 0)
	{
		m_position = sf::Vector2f(1019, m_aiSprite.getPosition().y);
		m_aiSprite.setPosition(m_position);
	}
	else if (m_aiSprite.getPosition().x >= 1020)
	{
		m_position = sf::Vector2f(1, m_aiSprite.getPosition().y);
		m_aiSprite.setPosition(m_position);
	}

	if (m_aiSprite.getPosition().y <= 0)
	{
		m_position = sf::Vector2f(m_aiSprite.getPosition().x, 1019);
		m_aiSprite.setPosition(m_position);
	}
	else if (m_aiSprite.getPosition().y >= 1020)
	{
		m_position = sf::Vector2f(m_aiSprite.getPosition().x, 1);
		m_aiSprite.setPosition(m_position);
	}
}

void AI::wander()
{
	timer++;

	if (timer > 50)
	{
		randValue = (rand() % 2) + 1;
		timer = 0;
	}

	if (randValue == 1)
	{
		randValue = 1;
	}
	else if(randValue == 2){
		randValue = -1;
	}

	sf::Vector2f normalizedVelocity = { m_velocity.x / getMagnitude(), m_velocity.y / getMagnitude() };

	m_orientation = getNewOrientation(m_orientation);
	m_orientation = m_orientation + maxRotation * randValue;
	normalizedVelocity.x = -sin(m_orientation) * maxSpeed.x;
	normalizedVelocity.y = cos(m_orientation) * maxSpeed.y;

	m_position += normalizedVelocity;
	m_aiSprite.setPosition(m_position);

	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees);
}

void AI::seek(sf::Vector2f& t_playerPosition)
{
	m_velocity = t_playerPosition - m_position;
	sf::Vector2f normalizedVelocity = { m_velocity.x / getMagnitude(), m_velocity.y / getMagnitude() };
	normalizedVelocity.x = normalizedVelocity.x * maxSpeed.x;
	normalizedVelocity.y = normalizedVelocity.y * maxSpeed.y;
	m_orientation = getNewOrientation(m_orientation);

	m_position += normalizedVelocity;
	m_aiSprite.setPosition(m_position);

	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees);
}

void AI::arrive(sf::Vector2f& t_playerPosition)
{
}

void AI::flee(sf::Vector2f& t_playerPosition)
{
	m_velocity = m_position - t_playerPosition;
	sf::Vector2f normalizedVelocity = { m_velocity.x / getMagnitude(), m_velocity.y / getMagnitude() };
	normalizedVelocity.x = normalizedVelocity.x * maxSpeed.x;
	normalizedVelocity.y = normalizedVelocity.y * maxSpeed.y;
	m_orientation = getNewOrientation(m_orientation);

	m_position += normalizedVelocity;
	m_aiSprite.setPosition(m_position);

	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees);
}

float AI::getNewOrientation(float t_currentOrientation)
{
	if (getMagnitude() > 0)
	{
		return atan2(-m_position.x, m_position.y);
	}
	else {
		return t_currentOrientation;
	}
}

float AI::getMagnitude()
{
	float magnitude = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	return magnitude;
}
