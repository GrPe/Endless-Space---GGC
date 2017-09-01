#include "Render.hpp"

void Render::draw()
{
	window.clear();
	//Enemies
	for (auto& x : alienArmyVector) window.draw(x.getSprite());
	//Bullets
	for (auto& x : bulletsVector) window.draw(x.getSprite());
	//Player
	window.draw(player.getSprite());
	window.display();
}

void Render::moveObjects()
{
	//bullets
	for (auto& x : bulletsVector) x.move();
	//aliens
	
}

void Render::check()
{
	//Player bullets
	std::vector<std::vector<Bullet>::iterator> temp;
	for (auto x = bulletsVector.begin(); x != bulletsVector.end(); x++)
	{
		if (x->getSprite().getPosition().y < 0) temp.push_back(x);
	}
	for (auto x : temp) bulletsVector.erase(x);
	temp.clear();

	//Enemy bullets


}

Render::Render(int x, int y) : xSize(x), ySize(y), window(sf::VideoMode(xSize, ySize),
	"Endless Space"), rs(10), distribution(2,4)
{
	player.deadEnd(100, 900.f, rs.getRes(0));
	window.setFramerateLimit(120);
	player.getSprite().setPosition(sf::Vector2f(xSize*0.5f, ySize*0.9f));
}

void Render::Start(unsigned int eir, unsigned int eic)
{
	//create army of enemies
	enemiesInRow = eir;
	enemiesInColumn = eic;
	amountOfEnemies = enemiesInRow * enemiesInColumn;
	for (unsigned int i = 0; i < amountOfEnemies; i++) alienArmyVector.push_back(Enemy(1, 600.0f, rs.getRes(distribution(generator))));
	//there are temp variable to set enemies position
	unsigned int r = 1;
	unsigned int c = 1;
	for (auto& x : alienArmyVector)
	{
		x.getSprite().setPosition((xSize*0.65f / enemiesInColumn)*c, (ySize*0.6 / enemiesInRow) * r);
		c++;
		if (c > enemiesInColumn)
		{
			r++;
			c = 1;
		}
		if (r > enemiesInRow) break; //is impossible, but...
	}
	
	//main loop of game
	while (window.isOpen())
	{
		events.CatchEvent(window,player, bulletsVector,rs.getRes(1));
		moveObjects();
		check();
		draw();
	}
}
