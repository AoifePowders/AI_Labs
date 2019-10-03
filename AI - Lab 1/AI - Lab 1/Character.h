#include <SFML/Graphics.hpp>
#include <iostream>
class Character
{
public:
	float m_acceleration = 0.0f;
	sf::Vector2f m_velocity{ 0, 0 };
	float m_rotation = 0.0f;
	sf::Vector2f m_position{ 0.0f, 0.0f };
	float maxSpeed = 10.0f;

	float m_radians;
	sf::Vector2f m_direction;
	float m_magnitude;
	float m_rotationSpeed = 0.1;

	void update();
	void render(sf::RenderWindow& t_window);
	void setUp(sf::Texture& t_texture, sf::Vector2f& t_position, sf::Vector2f& t_scale);
	void move();
	void boundary();
	void rotate();

	sf::CircleShape m_circle;
	float m_radius = 100;

private:
	sf::Sprite characterSprite;
};

