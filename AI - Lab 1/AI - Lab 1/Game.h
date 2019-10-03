#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "AI.h"

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

	sf::Texture m_aiTexture;
	sf::Texture m_shipTexture;

	sf::Font m_font;

	bool m_exitGame; // control exiting game

	Character player;
	AI seekAi;
	AI fleeAi;
	AI wanderAi;
	AI arriveAi;
	AI pursueAi;
};

#endif // !GAME_HPP

