#include "Render.hpp"

void Render::draw()
{
	window.draw(player.getSprite());
}

Render::Render(int x, int y) : xSize(x), ySize(y), window(sf::VideoMode(xSize,ySize),
	"Endless Space"), player(100,10.f,rs.getRes("player"))
{
	window.setFramerateLimit(60);
	player.getSprite().setPosition(sf::Vector2f(xSize*0.5f, ySize*0.8f));
}

void Render::Start()
{
	while (window.isOpen())
	{
		Events::CatchEvent(window);
		//moveEnemyArmy();
		//check();
		draw();
	}
}
