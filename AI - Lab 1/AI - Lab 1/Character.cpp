#include "Character.h"

void Character::changeVelocity()
{
}

void Character::setUp(sf::Texture &t_texture, sf::Vector2f& t_position, sf::Vector2f& t_scale, float t_rotation)
{
	characterSprite.setPosition(t_position);
	characterSprite.setScale(t_scale);
	characterSprite.setTexture(t_texture);
	characterSprite.setRotation(t_rotation);
	characterSprite.setOrigin(characterSprite.getTexture()->getSize().x / 2,characterSprite.getTexture()->getSize().x / 2);
}

void Character::move()
{
	characterSprite.setPosition(characterSprite.getPosition() + m_velocity);
}

void Character::boundary()
{
	if (characterSprite.getPosition().x <= 0)
	{
		characterSprite.setPosition(600 + 220, characterSprite.getPosition().y);
	}
	else if (characterSprite.getPosition().x >= 600 + 220)
	{
		characterSprite.setPosition(1, characterSprite.getPosition().y);
	}
}

void Character::render(sf::RenderWindow& t_window)
{
	t_window.draw(characterSprite);
}
