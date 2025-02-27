#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupSprite(); // load texture
	player.setUp(m_shipTexture, sf::Vector2f{ 400,500 }, sf::Vector2f{ 0.3f,0.3f });
	seekAi.setUp(m_aiTexture, m_font, sf::Vector2f{ 750,400 },sf::Vector2f{ 0.3f,0.3f }, "SEEK");
	//fleeAi.setUp(m_aiTexture, m_font, sf::Vector2f{ 600,400 }, sf::Vector2f{ 0.3f,0.3f }, "FLEE");
	wanderAi.setUp(m_aiTexture, m_font,sf::Vector2f{ 500,500 }, sf::Vector2f{ 0.3f,0.3f }, "WANDER");
	arriveAiSlow.setUp(m_aiTexture, m_font, sf::Vector2f{ 100,500 }, sf::Vector2f{ 0.3f,0.3f }, "ARRIVE SLOW");
	arriveAiFast.setUp(m_aiTexture, m_font, sf::Vector2f{ 100,500 }, sf::Vector2f{ 0.3f,0.3f }, "ARRIVE FAST");
	pursueAi.setUp(m_aiTexture, m_font, sf::Vector2f{ 100,500 }, sf::Vector2f{ 0.3f,0.3f }, "PURSUE");

}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Up == t_event.key.code)
	{
		player.m_acceleration += 0.01;
	}
	else if (sf::Keyboard::Down == t_event.key.code)
	{
		if (player.m_acceleration < 0)
		{
			player.m_acceleration = 0.0;
		}
		player.m_acceleration -= 0.01;
	}

	if (sf::Keyboard::Right == t_event.key.code)
	{
		player.m_rotation += 1.0f;
		player.m_rotationSpeed += 1.0f;
	}
	if (sf::Keyboard::Left == t_event.key.code)
	{
		player.m_rotation -= 1.0f;
		player.m_rotationSpeed -= 1.0f;
	}

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
} 

void Game::update(sf::Time t_deltaTime)
{
	player.update();
	player.boundary();

	seekAi.seek(player.m_position);
	wanderAi.wander(player.m_position);
	//fleeAi.flee(player.m_position);
	arriveAiSlow.arrive(player.m_position, 2);
	arriveAiFast.arrive(player.m_position, 6);
	pursueAi.pursue(player.m_position, player.m_velocity);

	//fleeAi.boundary();
	wanderAi.boundary();

	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear(sf::Color::White);
	player.render(m_window);
	seekAi.render(m_window);
	//fleeAi.render(m_window);
	wanderAi.render(m_window);
	arriveAiSlow.render(m_window);
	arriveAiFast.render(m_window);
	pursueAi.render(m_window);
	m_window.display();
}

void Game::setupSprite()
{
	if (!m_aiTexture.loadFromFile("ASSETS\\IMAGES\\AiShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	if (!m_shipTexture.loadFromFile("ASSETS\\IMAGES\\Ship.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}

	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
}
