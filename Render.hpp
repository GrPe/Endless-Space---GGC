#pragma once
#include "SFML\Graphics.hpp"
#include "Player.hpp"
#include "Events.hpp"
#include "Emeny.hpp"
#include "ResourceManager.hpp"
#include "Bullet.hpp"
#include <vector>
#include <random> //c++11 only

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
	bool isMovingLeft;
	bool isMovingRight;
	bool isMovingDown;
	//pair enemies how define movement of enemies;
	Enemy starter;
	Enemy ender;
	//to randomize textures of enemies (it is overkill I know)
	std::default_random_engine generator;
	//std::uniform_int_distribution<int> distribution;
	//to select enemy who can shoot


	//bullets
	std::vector<Bullet> bulletsVector;
	std::vector<Bullet> bulletsEnemyVector;

	void draw();
	void moveObjects();
	void check();
	bool win();
	bool failure();
	void enemyShoot(); 
	inline int getIntFromRange(int from, int to);

public:
	Render(int x, int y);
	void Start(unsigned int eir, unsigned int eic);
	//~Render();

	std::vector<Bullet>& getVectorOfBullets() { return bulletsVector; };
	ResourceManager& getRS() {return rs;};
	Player& getPlayer() { return player; };
};