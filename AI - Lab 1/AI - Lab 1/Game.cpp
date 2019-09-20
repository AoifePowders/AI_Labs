#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupSprite(); // load texture
	char1.setUp(m_shipTexture, sf::Vector2f{ 10,100 }, sf::Vector2f{ 0.3f,0.3f }, 90.0f);
	char2.setUp(m_sunTexture, sf::Vector2f{ 10,400 }, sf::Vector2f{ 0.3f,0.3f }, 0.0f);
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
		char1.m_velocity += char1.m_acceleration;
	}
	else if (sf::Keyboard::Down == t_event.key.code)
	{
		char1.m_velocity -= char1.m_acceleration;
	}

	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	char1.move();
	char2.move();

	char1.boundary();
	char2.boundary();

	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear(sf::Color::White);
	char1.render(m_window);
	char2.render(m_window);
	m_window.display();
}

void Game::setupSprite()
{
	if (!m_sunTexture.loadFromFile("ASSETS\\IMAGES\\sun.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	if (!m_shipTexture.loadFromFile("ASSETS\\IMAGES\\ship.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
}
