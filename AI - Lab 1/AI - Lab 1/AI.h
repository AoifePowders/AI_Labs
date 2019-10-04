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

	void setUp(sf::Texture& t_shipTexture, sf::Font& t_font,sf::Vector2f& t_position, sf::Vector2f& t_scale, sf::String t_name);
	void render(sf::RenderWindow& t_window);
	void boundary();

	//AI behaviour
	void wander(sf::Vector2f& t_playerPosition);
	void seek(sf::Vector2f& t_playerPosition);
	void arrive(sf::Vector2f& t_playerPosition, float t_maxSpeed);
	void flee(sf::Vector2f& t_playerPosition);
	void pursue(sf::Vector2f& t_playerPosition, sf::Vector2f& t_playerVelocity);

private:
	float getNewOrientation(sf::Vector2f t_vector);
	float getMagnitude(sf::Vector2f& t_vector);
	sf::Vector2f Normalize(sf::Vector2f t_vector);
	void playerDetection(sf::Vector2f& t_playerPosition);

private:
	sf::Vector2f m_position;
	float m_orientation = 0.0f;
	sf::Vector2f m_velocity{ 1, 1 };
	float m_rotation = -43.0f;
	float maxRotation = 360;
	float maxSpeed = 2;

	int m_timer = 0;
	float randValue;

	float timeToTarget = 0.25;
	float radius = 100;

	sf::Vector2f newTarget;
	float timePrediction = 40.0f;
	float maxTimePrediction = 40.0f;

private:
	sf::Sprite m_aiSprite;
	sf::Texture m_aiText;

	sf::Text name;

	sf::CircleShape triangle;
};

