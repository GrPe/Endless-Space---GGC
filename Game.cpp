#include "SFML\Graphics.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Endless Space");
	ResourceManager rs;
	Player player(3, 10.f, rs.getRes("player"));

	while (window.isOpen())
	{


		window.clear();
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}