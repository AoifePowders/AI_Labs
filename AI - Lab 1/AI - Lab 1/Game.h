#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Character.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupSprite();

	sf::RenderWindow m_window; // main SFML window

	sf::Texture m_sunTexture;
	sf::Texture m_shipTexture;
	bool m_exitGame; // control exiting game

	Character char1;
	Character char2;
};

#endif // !GAME_HPP

