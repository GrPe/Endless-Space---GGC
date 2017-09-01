#include "Render.hpp"

void Render::draw()
{
	window.clear();
	for (auto x : bulletsVector) window.draw(x.getSprite());
	window.draw(player.getSprite());
	window.display();
}

Render::Render(int x, int y) : xSize(x), ySize(y), window(sf::VideoMode(xSize, ySize),
	"Endless Space"), rs(10)
{
	player.deadEnd(100, 900.f, rs.getRes(0));
	window.setFramerateLimit(120);
	player.getSprite().setPosition(sf::Vector2f(xSize*0.5f, ySize*0.9f));
}

void Render::Start()
{
	while (window.isOpen())
	{
		events.CatchEvent(window,player, bulletsVector,rs.getRes(1));
		//moveEnemyArmy();
		//check();
		draw();
	}
}
