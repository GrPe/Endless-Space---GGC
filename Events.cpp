#include "Events.hpp"
#include "SFML\Graphics.hpp"

bool Events::pMoveLeft = false;
bool Events::pMoveRight = false;
bool Events::pShot = false;

void Events::CatchEvent(sf::RenderWindow& window)
{
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
				pMoveLeft = true;
				break;
			case sf::Keyboard::D:
				pMoveRight = true;
				break;
			case sf::Keyboard::Space:
				pShot = true;
				break;
			}
		}
		break;
		}
	}


}
