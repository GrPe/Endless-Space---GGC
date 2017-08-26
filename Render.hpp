#pragma once
#include "SFML\Graphics.hpp"
#include "Player.hpp"
#include "Events.hpp"
#include "ResourceManager.hpp"
#include "Emeny.hpp"
#include <vector>

class Render
{
private:
	const unsigned int xSize;
	const unsigned int ySize;
	sf::RenderWindow window;
	Player player;
	ResourceManager rs;
	std::vector<Enemy> alienArmyVector;
	struct Coordinates { int x; int y; };
	unsigned int amountOfEnemies;
	unsigned int enemiesInRow;
	unsigned int enemiesInColumn;

	void draw();
	void moveEnemyArmy();
	void check();
	bool win();
	bool failure();

public:
	Render(int x,int y);
	void Start();
	//~Render();
};