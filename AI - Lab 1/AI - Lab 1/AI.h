#include <iostream>
#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

class AI
{
public:
	AI();
	~AI();

	void setUp(sf::Texture& t_shipTexture, sf::Vector2f& t_position, sf::Vector2f& t_scale);
	void render(sf::RenderWindow& t_window);
	void boundary();

	void wander();
	void seek(sf::Vector2f& t_playerPosition);
	void arrive(sf::Vector2f& t_playerPosition);
	void flee(sf::Vector2f& t_playerPosition);
	void pursue(sf::Vector2f& t_playerPosition);

	int timer = 0;

	float getNewOrientation();

	float getMagnitude(sf::Vector2f& t_vector);
	sf::Vector2f Normalize(sf::Vector2f t_vector);

	sf::Vector2f m_position;
	float m_orientation = 0.0f;
	sf::Vector2f m_velocity{ 1, 1 };
	float m_rotation = -43.0f;
	float maxRotation = 360;
	sf::Vector2f m_maxVelocity{ 10,10 };
	sf::Vector2f m_desiredVelocity{ 0,0 };
	sf::Vector2f m_steering{ 0,0 };
	float m_maxForce = 10;

	float randValue;

	sf::Vector2f maxSpeed{ 2,2 };

private:
	sf::Sprite m_aiSprite;
	sf::Texture m_aiText;
};

