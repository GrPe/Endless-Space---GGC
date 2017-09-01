#pragma once
#include "SFML\Graphics.hpp"
#include "Player.hpp"
#include "Events.hpp"
#include "Emeny.hpp"
#include "ResourceManager.hpp"
#include "Bullet.hpp"
#include <vector>

class Render
{
private:
	//map
	const unsigned int xSize;
	const unsigned int ySize;
	sf::RenderWindow window;
	ResourceManager rs;

	//player
	Player player;
	Events events;

	//enemies
	std::vector<Enemy> alienArmyVector;
	unsigned int amountOfEnemies;
	unsigned int enemiesInRow;
	unsigned int enemiesInColumn;

	//bullets
	std::vector<Bullet> bulletsVector;

	void draw();
	void moveObjects();
	void check();
	bool win();
	bool failure();

public:
	Render(int x, int y);
	void Start();
	//~Render();

	std::vector<Bullet>& getVectorOfBullets() { return bulletsVector; };
	ResourceManager& getRS() {return rs;};
	Player& getPlayer() { return player; };
};