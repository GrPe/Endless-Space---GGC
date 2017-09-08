#include "Events.hpp"
#include "SFML\Graphics.hpp"
#include <iostream>

void Events::CatchEvent(sf::RenderWindow& window, Player& player, std::vector <Bullet>& vb, sf::Texture& tx)
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
			case sf::Keyboard::Escape:
				window.close();
				break;
			case sf::Keyboard::A:
				player.moveLeft();
				break;
			case sf::Keyboard::D:
				player.moveRight();
				break;
			case sf::Keyboard::Space:
				player.shot(vb, tx);
				break;
			}
		}
		}
	}
}

void Events::WinEvent(sf::RenderWindow & window)
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed) window.close(); //END
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window.close(); //END
	}
}
