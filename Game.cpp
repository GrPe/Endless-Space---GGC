#include "Game.hpp"

void Game::drawGame()
{
	window.clear();
	//GUI
	window.draw(scoreLabel);
	for (int x = 0; x < player.getHPCurrent(); x++) window.draw(HPSprites[x]);
	//Enemy's Bullets
	for (auto& x : bulletsEnemyVector) window.draw(x.getSprite());
	//Enemies
	for (auto& x : alienArmyVector) window.draw(x.getSprite());
	//Bullets
	for (auto& x : bulletsVector) window.draw(x.getSprite());
	//Player
	window.draw(player.getSprite());

	window.display();
}

void Game::createEnemies(unsigned int eir, unsigned int eic)
{
	enemiesInRow = eir;
	enemiesInColumn = eic;
	amountOfEnemies = enemiesInRow * enemiesInColumn;
	for (unsigned int i = 0; i < amountOfEnemies; i++) alienArmyVector.push_back(Enemy(1, 180.0f, rs.getTexture(getIntFromRange(2, 4))));
	//there are temp variable to set enemies position
	unsigned int r = 1;
	unsigned int c = 1;
	for (auto& x : alienArmyVector)
	{
		x.getSprite().setPosition((xSize*0.65f / enemiesInColumn)*c, (ySize*0.6f / enemiesInRow) * r);
		c++;
		if (c > enemiesInColumn)
		{
			r++;
			c = 1;
		}
		if (r > enemiesInRow) break; //is impossible, but...
	}

	starter = alienArmyVector[0];
	ender = alienArmyVector[amountOfEnemies - 1];
}

void Game::checkEnemyCollision()
{
	if (ender.getSprite().getPosition().x > xSize*0.97f && isMovingRight)
	{
		isMovingRight = false;
		isMovingDown = true;
	}
	else if (ender.getSprite().getPosition().x > xSize*0.97f && isMovingDown)
	{
		isMovingDown = false;
		isMovingLeft = true;
	}
	else if (starter.getSprite().getPosition().x < xSize*0.03f && isMovingLeft)
	{
		isMovingLeft = false;
		isMovingDown = true;
	}
	else if (starter.getSprite().getPosition().x < xSize*0.03f && isMovingDown)
	{
		isMovingDown = false;
		isMovingRight = true;
	}
}

void Game::moveEnemies()
{
	if (isMovingLeft)
	{
		for (auto& x : alienArmyVector) x.moveLeft();
		starter.moveLeft();
		ender.moveLeft();
	}
	else if (isMovingRight)
	{
		for (auto& x : alienArmyVector) x.moveRight();
		starter.moveRight();
		ender.moveRight();
	}
	else if (isMovingDown)
	{
		for (auto& x : alienArmyVector) x.moveDown();
		starter.moveDown();
		ender.moveDown();
	}
}

void Game::moveBullets()
{
	for (auto& x : bulletsVector) x.move();
	for (auto& x : bulletsEnemyVector) x.move();
}

void Game::deletePlayerBullets()
{
	for (auto x = bulletsVector.begin(); x != bulletsVector.end(); x++)
	{
		if (x->getSprite().getPosition().y < 0) bulletsToRemove.push_back(x);
	}
	for (auto x : bulletsToRemove) bulletsVector.erase(x);
	bulletsToRemove.clear();
}

void Game::hitsDetectionPlayer()
{
	float playerXMinPosition = player.getSprite().getPosition().x - player.getSprite().getTexture()->getSize().x*0.2f;
	float playerXMaxPosition = player.getSprite().getPosition().x + player.getSprite().getTexture()->getSize().x*0.2f;
	for (auto bullet = bulletsEnemyVector.begin(); bullet != bulletsEnemyVector.end(); bullet++)
	{
		float bulletXPosition = bullet->getSprite().getPosition().x;
		float bulletYPosition = bullet->getSprite().getPosition().y;
		if (bulletYPosition >= player.getSprite().getPosition().y)
		{
			if (bulletXPosition > playerXMinPosition && bulletXPosition < playerXMaxPosition)
			{
				player.getDamage();
				bulletsEnemyToRemove.push_back(bullet);
			}
		}
	}
	for (auto& x : bulletsEnemyToRemove) bulletsEnemyVector.erase(x);
	bulletsEnemyToRemove.clear();
}

inline void Game::finishGame()
{
	finish = true;
}

void Game::VictoryCheck()
{
	//Win Conditions:
	//-- destroy all enemies
	if (alienArmyVector.size() <= 0)
	{
		finishGame();
		drawFailure();
	}
}

void Game::FailCheck()
{
	if (player.getHPCurrent() <= 0)
	{
		finishGame();
		drawFailure();
	}
}

inline void Game::addPoints()
{
	scoreCounter++;
	scoreLabel.setString("Score: " + std::to_string(scoreCounter));
}

inline void Game::addPoints(unsigned int x)
{
	scoreCounter += x;
	scoreLabel.setString("Score:" + std::to_string(scoreCounter));
}

void Game::drawWin()
{
	sf::Font font;
	font.loadFromFile("src/font.ttf");
	sf::Text text("YOU WIN!",font);
	sf::Text text2("Press ESC to exit",font);
	text.setCharacterSize(80);
	text2.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text2.setFillColor(sf::Color::White);
	text.setPosition(xSize*0.5f-140, ySize*0.5f-120);
	text2.setPosition(xSize*0.5f-120, ySize*0.5f +80);
	while (window.isOpen())
	{
		window.clear();
		window.draw(text);
		window.draw(text2);
		window.display();
		events.WinEvent(window);
	}
}

void Game::drawFailure()
{
	sf::Font font;
	font.loadFromFile("src/font.ttf");
	sf::Text text("YOU LOST", font);
	sf::Text text2("Press ESC to exit", font);
	text.setCharacterSize(80);
	text2.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text2.setFillColor(sf::Color::White);
	text.setPosition(xSize*0.5f - 140, ySize*0.5f - 120);
	text2.setPosition(xSize*0.5f - 120, ySize*0.5f + 80);
	while(window.isOpen())
	{
		window.clear();
		window.draw(text);
		window.draw(text2);
		window.display();
		events.WinEvent(window);
	}
}

void Game::enemyShoot()
{
	if (getIntFromRange(1, 100) % 50 == 0) // Amount of enemy's bullets
	{
		int temp = getIntFromRange(0, alienArmyVector.size() - 1);
		alienArmyVector[temp].shot(bulletsEnemyVector, rs.getTexture(1));
	}
}

void Game::hitsDetectionEnemies()
{
	for (auto enemy = alienArmyVector.begin(); enemy != alienArmyVector.end(); enemy++)
	{
		float rangeMinX = enemy->getSprite().getPosition().x - enemy->getSprite().getTexture()->getSize().x*0.175f;
		float rangeMaxX = enemy->getSprite().getPosition().x + enemy->getSprite().getTexture()->getSize().x*0.175f;
		float rangeYMin = enemy->getSprite().getPosition().y; //- enemy->getSprite().getTexture()->getSize().y*0.175f;
		float rangeYMax = enemy->getSprite().getPosition().y + enemy->getSprite().getTexture()->getSize().y*0.175f;
		for (auto bullet = bulletsVector.begin(); bullet != bulletsVector.end(); bullet++)
		{
			float bulletXPosition = bullet->getSprite().getPosition().x;
			float bulletYPosition = bullet->getSprite().getPosition().y;
			if (bulletXPosition >= rangeMinX && bulletXPosition <= rangeMaxX && bulletYPosition >= rangeYMin && bulletYPosition <= rangeYMax)
			{
				deadEnemies.push_back(enemy);
				bulletsToRemove.push_back(bullet);
				addPoints();
			}
		}
	}
	for (auto x : bulletsToRemove) bulletsVector.erase(x);
	bulletsToRemove.clear();

	for (auto& x : deadEnemies) alienArmyVector.erase(x);
	deadEnemies.clear();
}

void Game::deleteEnemiesBullets()
{
	for (auto x = bulletsEnemyVector.begin(); x != bulletsEnemyVector.end(); x++)
	{
		if (x->getSprite().getPosition().y > ySize) bulletsEnemyToRemove.push_back(x);
	}
	for (auto x : bulletsEnemyToRemove) bulletsEnemyVector.erase(x);
	bulletsEnemyToRemove.clear();
}

int Game::getIntFromRange(int from, int to)
{
	std::uniform_int_distribution<int> distribution(from,to);
	return distribution(generator);
}

Game::Game(int x, int y) : xSize(x), ySize(y), window(sf::VideoMode(xSize, ySize),
	"Endless Space"), rs(10), finish(false), scoreCounter(0), scoreLabel("Score: 0", rs.getFont())
{
	//Player
	player.deadEnd(3, 900.f, rs.getTexture(0));
	player.getSprite().setPosition(sf::Vector2f(xSize*0.5f, ySize*0.9f));
	//Window
	window.setFramerateLimit(120);
	//Labels
	scoreLabel.setPosition(xSize - 220.0f,10.0f);
	scoreLabel.setCharacterSize(NORMALTEXTSIZE);
	//HP
	for (int i = 0; i < player.getHPMax(); i++) HPSprites.push_back(sf::Sprite(rs.getTexture(5)));
	int counter = 0;
	for (auto& x : HPSprites)
	{
		x.setOrigin(x.getTexture()->getSize().x*0.5f, x.getTexture()->getSize().y*0.5f);
		x.setPosition(20.0f+ 30.0f*counter++, 32.0f);
	}
}

void Game::Start(unsigned int eir, unsigned int eic)
{
	//Create Enemies
	createEnemies(eir, eic);

	//start movement of enemies --TODO
	isMovingRight = true;
	
	//main loop of game
	while (window.isOpen())
	{
		events.CatchEvent(window,player, bulletsVector,rs.getTexture(1));
		moveBullets();
		moveEnemies();
		checkEnemyCollision();
		enemyShoot();
		hitsDetectionEnemies();
		deletePlayerBullets();
		deleteEnemiesBullets();
		hitsDetectionPlayer();
		VictoryCheck();
		FailCheck();
		drawGame();
		if (finish) break; //End of game
	}
}
