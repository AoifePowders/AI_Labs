#include "AI.h"

AI::AI()
{
}

AI::~AI()
{
}

void AI::setUp(sf::Texture& t_aiTexture, sf::Font& t_font, sf::Vector2f& t_position, sf::Vector2f& t_scale, sf::String t_name)
{
	m_position = t_position;
	m_aiSprite.setPosition(m_position);
	m_aiSprite.setRotation(m_rotation);
	m_aiSprite.setTexture(t_aiTexture);
	m_aiSprite.setOrigin(m_aiSprite.getTexture()->getSize().x / 2, m_aiSprite.getTexture()->getSize().y / 2);
	m_aiSprite.setScale(t_scale);

	name.setCharacterSize(20);
	name.setFillColor(sf::Color::Black);
	name.setFont(t_font);
	name.setPosition(m_position);
	name.setString(t_name);

	FOV = sf::VertexArray(sf::Triangles, 3);
	// define the position of the triangle's points
	FOV[0].position = sf::Vector2f(m_position);
	FOV[1].position = sf::Vector2f(100.f, 10.f);
	FOV[2].position = sf::Vector2f(100.f, 100.f);

	// define the color of the triangle's points
	FOV[0].color = sf::Color(255,0,0,100);
	FOV[1].color = sf::Color(255, 0, 0, 100);
	FOV[2].color = sf::Color(255, 0, 0, 100);
}

void AI::render(sf::RenderWindow& t_window)
{
	t_window.draw(FOV);
	t_window.draw(m_aiSprite);
	t_window.draw(name);
}

//screen wrapping
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

//AI that randomly moves around
void AI::wander()
{
	srand(time(0));
	m_timer++;

	if (m_timer > 50)
	{
		randValue = (rand() % 2) + 1;
		m_timer = 0;
	}

	if (randValue == 1)
	{
		randValue = 1;
	}
	else if(randValue == 2){
		randValue = -1;
	}

	sf::Vector2f normalizedVelocity = { Normalize(m_velocity) };

	m_orientation = getNewOrientation(m_velocity);
	m_orientation = m_orientation + maxRotation * randValue;
	normalizedVelocity.x = -sin(m_orientation) * maxSpeed.x;
	normalizedVelocity.y = cos(m_orientation) * maxSpeed.y;

	m_position += normalizedVelocity;
	m_aiSprite.setPosition(m_position);

	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 90);

	//// define the position of the triangle's points
	FOV[0].position = sf::Vector2f(m_position);
	FOV[1].position = sf::Vector2f(m_position.x + 100, m_position.y + 100);
	FOV[2].position = sf::Vector2f(m_position.x + 100, m_position.y - 100);

	name.setPosition(m_position);

}

//AI that seeks out the player
void AI::seek(sf::Vector2f& t_playerPosition)
{
	m_velocity = t_playerPosition - m_position;
	m_orientation = getNewOrientation(m_velocity);

	sf::Vector2f normalizedVelocity = { m_velocity.x / getMagnitude(m_velocity), m_velocity.y / getMagnitude(m_velocity) };
	m_position.x += normalizedVelocity.x * maxSpeed.x;
	m_position.y += normalizedVelocity.y * maxSpeed.y;
	m_aiSprite.setPosition(m_position);

	//makes ai look in direction its moving
	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 90);

	//// define the position of the triangle's points
	FOV[0].position = sf::Vector2f(m_position);
	FOV[1].position = sf::Vector2f(m_position.x + 100, m_position.y + 100);
	FOV[2].position = sf::Vector2f(m_position.x + 100, m_position.y - 100);

	name.setPosition(m_position);
}

//AI that arrives at the player
void AI::arrive(sf::Vector2f& t_playerPosition)
{
	m_velocity = t_playerPosition - m_position;
	m_orientation = getNewOrientation(m_velocity);
	if (getMagnitude(m_velocity) < radius)
	{
	}
	else if (getMagnitude(m_velocity) > maxSpeed.x)
	{
		m_velocity.x = m_velocity.x / timeToTarget;
		m_velocity.y = m_velocity.y / timeToTarget;

		if (getMagnitude(m_velocity) > maxSpeed.x)
		{
			m_velocity.x = (m_velocity.x / getMagnitude(m_velocity));
			m_velocity.y = (m_velocity.y / getMagnitude(m_velocity));
			m_velocity.x = m_velocity.x * 0.5;
			m_velocity.y = m_velocity.y * 0.5;

		}

		m_position += m_velocity;
	}
	
	m_aiSprite.setPosition(m_position);

	//makes ai look in direction its moving
	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 90);

	//// define the position of the triangle's points
	FOV[0].position = sf::Vector2f(m_position);
	FOV[1].position = sf::Vector2f(m_position.x + 100, m_position.y + 100);
	FOV[2].position = sf::Vector2f(m_position.x + 100, m_position.y - 100);

	name.setPosition(m_position);

}

//AI that flees from the player
void AI::flee(sf::Vector2f& t_playerPosition)
{
	m_velocity = m_position - t_playerPosition;
	m_orientation = getNewOrientation(m_velocity);

	sf::Vector2f normalizedVelocity = { m_velocity.x / getMagnitude(m_velocity), m_velocity.y / getMagnitude(m_velocity) }; 
	normalizedVelocity.x = normalizedVelocity.x * maxSpeed.x;
	normalizedVelocity.y = normalizedVelocity.y * maxSpeed.y;

	m_position += normalizedVelocity;
	m_aiSprite.setPosition(m_position);

	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 90);

	//// define the position of the triangle's points
	FOV[0].position = sf::Vector2f(m_position);
	FOV[1].position = sf::Vector2f(m_position.x + 100, m_position.y + 100);
	FOV[2].position = sf::Vector2f(m_position.x + 100, m_position.y - 100);

	name.setPosition(m_position);

}

void AI::pursue(sf::Vector2f& t_playerPosition, sf::Vector2f& t_playerVelocity)
{
	m_velocity = t_playerPosition - m_position;
	float distance = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));

	if (getMagnitude(m_velocity) <= distance / prediction)
	{
		predictedDistance = prediction;
	}
	else{
		predictedDistance = distance / getMagnitude(m_velocity);
	}
	newTarget = t_playerPosition + t_playerVelocity * predictedDistance;
	seek(newTarget);

	FOV[0].position = sf::Vector2f(m_position);
	FOV[1].position = sf::Vector2f(m_position.x + 100, m_position.y + 100);
	FOV[2].position = sf::Vector2f(m_position.x + 100, m_position.y - 100);
}

//returns the orientation of the AI
float AI::getNewOrientation(sf::Vector2f t_vector)
{
	return atan2(t_vector.y, t_vector.x);
}

//finds the magnitude of the AI
float AI::getMagnitude(sf::Vector2f& t_vector)
{
	float magnitude = sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y));
	return magnitude;
}

//returns the normalised vector 
sf::Vector2f AI::Normalize(sf::Vector2f t_vector)
{
	sf::Vector2f normalizedVector{ 0,0 };
	normalizedVector = t_vector / (sqrt((t_vector.x * t_vector.x) + (t_vector.y * t_vector.y)));
	return normalizedVector;
}
