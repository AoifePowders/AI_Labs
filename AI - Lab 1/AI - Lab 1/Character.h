#include <SFML/Graphics.hpp>
#include <iostream>
class Character
{
public:
	sf::Vector2f m_acceleration{ 0.1f, 0 };
	sf::Vector2f m_velocity{ 1, 0 };

	void changeVelocity();
	void render(sf::RenderWindow& t_window);
	void setUp(sf::Texture& t_texture, sf::Vector2f& t_position, sf::Vector2f& t_scale, float t_rotation);
	void move();
	void boundary();
private:
	sf::Sprite characterSprite;
};

