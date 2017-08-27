#include "Events.hpp"
#include "SFML\Graphics.hpp"
#include <iostream>


void Events::CatchEvent(sf::RenderWindow& window, Player& player)
{
	pMoveLeft = false;
	pMoveRight = false;
	pShot = false;

	sf::Event e;
	while (window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
		{
			switch (e.key.code)
			{
			case sf::Keyboard::A:
				player.moveLeft();
				break;
			case sf::Keyboard::D:
				player.moveRight();
				break;
			case sf::Keyboard::Space:
				break;
			}
		}
		break;
		}
	}
}
