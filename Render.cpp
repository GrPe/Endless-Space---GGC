#include "Render.hpp"

void Render::draw()
{
	window.clear();
	window.draw(player.getSprite());
	window.display();
}

Render::Render(int x, int y) : xSize(x), ySize(y), window(sf::VideoMode(xSize, ySize),
	"Endless Space")
{
	pTexture.loadFromFile("src/player.png");
	player.deadEnd(100, 900.f, pTexture);
	window.setFramerateLimit(120);
	player.getSprite().setPosition(sf::Vector2f(xSize*0.5f, ySize*0.8f));
}

void Render::Start()
{
	while (window.isOpen())
	{
		e.CatchEvent(window, player);
		//moveEnemyArmy();
		//check();
		draw();
	}
}
