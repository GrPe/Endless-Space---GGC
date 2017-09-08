#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Player.hpp"
#include "Events.hpp"
#include "Emeny.hpp"
#include "ResourceManager.hpp"
#include "Bullet.hpp"
#include "Building.hpp"
#include <vector>
#include <list>
#include <string>
#include <random> //c++11 only

class Game
{
private:
	//Audio
	sf::Music music;

	//Play control
	bool finish;
	unsigned int scoreCounter;

	//GUI
	sf::Text scoreLabel;
	sf::Text failWinLabel;
	sf::Text infoLabelNormal;
	sf::Text endingScoreLabel;
	const unsigned int NORMALTEXTSIZE = 30;
	const unsigned int BIGTEXTSIZE = 80;
	std::vector<sf::Sprite> HPSprites;
	const std::string failString = "GAME OVER!";
	const std::string winString = "YOU WIN!";
	const std::string defaultEndMessageString = "Press ESC to exit";
	const std::string scoreMessageString = "Your Score: ";

	//map
	const unsigned int xSize;
	const unsigned int ySize;
	sf::RenderWindow window;
	ResourceManager rs;

	//player
	Player player;
	Events events;

	//Enemies
	std::vector<Enemy> alienArmyVector;
	std::vector<std::vector<Enemy>::iterator> deadEnemies; //table of dead enemies to remove
	unsigned int amountOfEnemies;
	unsigned int enemiesInRow;
	unsigned int enemiesInColumn;
	//Enemies Collision
	bool isMovingLeft;
	bool isMovingRight;
	bool isMovingDown;
	//pair enemies how define movement of enemies;
	Enemy starter;
	Enemy ender;
	//to randomize textures of enemies (it is overkill I know)
	//&& to select enemy who can shoot
	std::default_random_engine generator;

	//bullets
	std::vector<std::vector<Bullet>::iterator> bulletsToRemove; //table of player's bullets to remove
	std::vector<std::list<Bullet>::iterator> bulletsEnemyToRemove; //list of enemy's bullets to remove
	std::vector<Bullet> bulletsVector;
	std::list<Bullet> bulletsEnemyVector;

	//Buildings
	std::list<Building> buildings; 
	std::list<std::list<Building>::iterator> buildingsToRemove;

	//Functions
	//Display:
	void drawGame();
	void drawEnd(bool result);
	//Enemies
	void createEnemies(unsigned int eir, unsigned int eic);
	void checkEnemyCollision();
	void moveEnemies();
	void enemyShoot();
	void hitsDetectionEnemies();
	void crossDownLineCheck();
	//Bullets
	void deleteEnemiesBullets();
	void deletePlayerBullets();
	void moveBullets();
	//Player
	void hitsDetectionPlayer();
	//Win-Fail checkers
	inline void finishGame();
	void VictoryCheck();
	void FailCheck();
	inline void addPoints();
	inline void addPoints(unsigned int x); //For special enemy
	//Randomize
	inline int getIntFromRange(int from, int to);
	//Buildings
	void hitsDetectionBuildings();
	void createBuildings();
	void destroyBuildings();

public:
	Game(int x, int y);
	void Start(unsigned int eir, unsigned int eic);
};