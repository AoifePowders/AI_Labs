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

	triangle.setPointCount(3);
	triangle.setRadius(100);
	triangle.setPosition(m_position);
	triangle.setFillColor(sf::Color(255, 0, 0, 100));
	triangle.setOrigin(triangle.getPoint(1));
}

void AI::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_aiSprite);
	t_window.draw(name);
	t_window.draw(triangle);
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
void AI::wander(sf::Vector2f& t_playerPosition)
{
	//seed for random number generator
	srand(time(0));
	//timer that tells the ai when to switch direction
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

	//move and rotate 
	sf::Vector2f normalizedVelocity = { Normalize(m_velocity) };
	m_orientation = getNewOrientation(normalizedVelocity);
	m_orientation = m_orientation + maxRotation * randValue;
	normalizedVelocity.x = -sin(m_orientation) * maxSpeed;
	normalizedVelocity.y = cos(m_orientation) * maxSpeed;

	m_position += normalizedVelocity;
	m_aiSprite.setPosition(m_position);

	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 180);

	triangle.setRotation(degrees + 250);
	playerDetection(t_playerPosition);

	name.setPosition(m_position);
}

//AI that seeks out the player
void AI::seek(sf::Vector2f& t_playerPosition)
{
	m_velocity = t_playerPosition - m_position;
	m_orientation = getNewOrientation(m_velocity);

	sf::Vector2f normalizedVelocity = { m_velocity.x / getMagnitude(m_velocity), m_velocity.y / getMagnitude(m_velocity) };
	m_position.x += normalizedVelocity.x * maxSpeed;
	m_position.y += normalizedVelocity.y * maxSpeed;
	m_aiSprite.setPosition(m_position);

	//makes ai look in direction its moving
	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 90);

	triangle.setRotation(degrees + 160);
	playerDetection(t_playerPosition);

	name.setPosition(m_position);
}

//AI that arrives at the player
void AI::arrive(sf::Vector2f& t_playerPosition, float t_maxSpeed)
{
	m_velocity = t_playerPosition - m_position;
	m_orientation = getNewOrientation(m_velocity);

	//length of velocity is less than radius
	if (getMagnitude(m_velocity) > radius)
	{
		//the ai is within the radius of the player circle
		//and should slow down
		m_velocity.x = m_velocity.x / timeToTarget;
		m_velocity.y = m_velocity.y / timeToTarget;

		if (getMagnitude(m_velocity) > t_maxSpeed)
		{
			m_velocity.x = (m_velocity.x / getMagnitude(m_velocity));
			m_velocity.y = (m_velocity.y / getMagnitude(m_velocity));
			m_velocity.x = m_velocity.x * t_maxSpeed;
			m_velocity.y = m_velocity.y * t_maxSpeed;
		}

		m_position += m_velocity;
	}
	
	m_aiSprite.setPosition(m_position);

	//makes ai look in direction its moving
	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 90);

	triangle.setRotation(degrees + 160);
	playerDetection(t_playerPosition);

	name.setPosition(m_position);

}

//AI that flees from the player
void AI::flee(sf::Vector2f& t_playerPosition)
{
	m_velocity = m_position - t_playerPosition;
	m_orientation = getNewOrientation(m_velocity);

	sf::Vector2f normalizedVelocity = { m_velocity.x / getMagnitude(m_velocity), m_velocity.y / getMagnitude(m_velocity) }; 
	normalizedVelocity.x = normalizedVelocity.x * maxSpeed;
	normalizedVelocity.y = normalizedVelocity.y * maxSpeed;

	m_position += normalizedVelocity;
	m_aiSprite.setPosition(m_position);

	float degrees = m_orientation * (180 / 3.14159);
	m_aiSprite.setRotation(degrees + 90);

	name.setPosition(m_position);
}

//finds a point in front of the player and moves to that
void AI::pursue(sf::Vector2f& t_playerPosition, sf::Vector2f& t_playerVelocity)
{
	sf::Vector2f direction = t_playerPosition - m_position;
	float distance = getMagnitude(direction);

	if (getMagnitude(m_velocity) <= distance / maxTimePrediction)
	{
		timePrediction = maxTimePrediction;
	}
	else{
		timePrediction = distance / getMagnitude(m_velocity);
	}
	newTarget = t_playerPosition + t_playerVelocity * timePrediction;
	seek(newTarget);

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

void AI::playerDetection(sf::Vector2f& t_playerPosition)
{
	triangle.setPosition(m_position.x, m_position.y);
	if (triangle.getGlobalBounds().contains(t_playerPosition))
	{
		triangle.setFillColor(sf::Color(0, 255, 0, 100));
	}
	else
	{
		triangle.setFillColor(sf::Color(255, 0, 0, 100));
	}
}
