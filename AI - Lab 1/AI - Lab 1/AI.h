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

	int timer = 0;

	float getNewOrientation(float currentOrientation);

	float getMagnitude();

	sf::Vector2f m_position;
	float m_orientation = 0.0f;
	sf::Vector2f m_velocity{ 0,0 };
	float m_rotation = -43.0f;
	float maxRotation = 360;

	float randValue;

	sf::Vector2f maxSpeed{ 1,1 };

private:
	sf::Sprite m_aiSprite;
	sf::Texture m_aiText;
};

