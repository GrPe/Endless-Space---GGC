#include "Game.hpp"

void Game::drawGame()
{
	window.clear();
	//GUI
	window.draw(scoreLabel);
	for (int x = 0; x < player.getHPCurrent(); x++) window.draw(HPSprites[x]);
	//Enemy's Bullets
	for (auto& x : bulletsEnemyVector) window.draw(x.getSprite());
	//Buildings
	for (auto& x : buildings) window.draw(x.getSprite());
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
		x.getSprite().setPosition((xSize*0.45f / enemiesInColumn)*c, (ySize*0.5f / enemiesInRow) * r);
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
		drawEnd(true);
	}
}

void Game::FailCheck()
{
	if (player.getHPCurrent() <= 0)
	{
		finishGame();
		drawEnd(false);
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

void Game::drawEnd(bool result)
{
	if (result) failWinLabel.setString(winString);
	else failWinLabel.setString(failString);
	infoLabelNormal.setString(defaultEndMessageString);
	endingScoreLabel.setString(scoreMessageString + std::to_string(scoreCounter));
	failWinLabel.setOrigin(failWinLabel.getLocalBounds().width*0.5f, failWinLabel.getLocalBounds().height*0.5f);
	infoLabelNormal.setOrigin(infoLabelNormal.getLocalBounds().width*0.5f, infoLabelNormal.getLocalBounds().height*0.5f);
	endingScoreLabel.setOrigin(endingScoreLabel.getLocalBounds().width*0.5f, endingScoreLabel.getLocalBounds().height*0.5f);
	while (window.isOpen())
	{
		window.clear();
		window.draw(failWinLabel);
		window.draw(endingScoreLabel);
		window.draw(infoLabelNormal);
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
		float rangeMinX = enemy->getSprite().getPosition().x - enemy->getSprite().getTexture()->getSize().x*0.14f;
		float rangeMaxX = enemy->getSprite().getPosition().x + enemy->getSprite().getTexture()->getSize().x*0.14f;
		float rangeYMin = enemy->getSprite().getPosition().y;
		float rangeYMax = enemy->getSprite().getPosition().y + enemy->getSprite().getTexture()->getSize().y*0.14f;
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

void Game::crossDownLineCheck()
{
	for (auto& x : alienArmyVector)
	{
		if (x.getSprite().getPosition().y >= player.getSprite().getPosition().y - 50.0f)
		{
			finishGame();
			player.kill();
			FailCheck();
		}
	}
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

void Game::hitsDetectionBuildings()
{
	for (auto& building : buildings)
	{
		float maxLeft = building.getSprite().getPosition().x - building.getSprite().getTexture()->getSize().x*0.5f*1.2f;
		float maxRight = building.getSprite().getPosition().x + building.getSprite().getTexture()->getSize().x * 0.5f*1.2f;
		float maxUp = building.getSprite().getPosition().y - building.getSprite().getTexture()->getSize().y * 0.5f*1.2f;
		for (auto bullet = bulletsEnemyVector.begin();bullet != bulletsEnemyVector.end();bullet++)
		{
			float xBulletCoor = bullet->getSprite().getPosition().x;
			float yBulletCoor = bullet->getSprite().getPosition().y;
			if (xBulletCoor > maxLeft && xBulletCoor < maxRight && yBulletCoor > maxUp)
			{
				building.getDamage();
				bulletsEnemyToRemove.push_back(bullet);
			}
		}
	}
	for (auto& x : bulletsEnemyToRemove) bulletsEnemyVector.erase(x);
	bulletsEnemyToRemove.clear();
	destroyBuildings();
}

void Game::createBuildings()
{
	for (int i = 0; i < 5; i++) buildings.push_back(Building(rs));
	int counter = 0;
	for (auto& x : buildings) x.getSprite().setPosition(300.0f + counter++ * 350.0f, player.getSprite().getPosition().x - 120.0f);
}

void Game::destroyBuildings()
{
	for (auto x = buildings.begin(); x != buildings.end(); x++) if (x->getHPCurrent() <= 0) buildingsToRemove.push_back(x);
	for (auto x : buildingsToRemove) buildings.erase(x);
	buildingsToRemove.clear();
}

Game::Game(int x, int y) : xSize(x), ySize(y), window(sf::VideoMode(xSize, ySize),
	"Endless Space", sf::Style::Fullscreen),rs(), finish(false), scoreCounter(0), scoreLabel("Score: 0", rs.getFont()),
	failWinLabel("", rs.getFont()), infoLabelNormal("", rs.getFont()), endingScoreLabel("", rs.getFont())
{
	//Player
	player.deadEnd(3, 900.f, rs.getTexture(0), rs.getSB());
	player.getSprite().setPosition(sf::Vector2f(xSize*0.5f, ySize*0.9f));
	//Window
	window.setFramerateLimit(120);
	//Labels
	scoreLabel.setPosition(xSize - 220.0f,10.0f);
	scoreLabel.setCharacterSize(NORMALTEXTSIZE);

	failWinLabel.setCharacterSize(BIGTEXTSIZE);
	failWinLabel.setPosition(xSize*0.5f, ySize*0.5f);

	infoLabelNormal.setCharacterSize(NORMALTEXTSIZE);
	infoLabelNormal.setPosition(xSize*0.5f, ySize*0.5f + 80.0f);

	endingScoreLabel.setCharacterSize(NORMALTEXTSIZE);
	endingScoreLabel.setPosition(xSize*0.5f, ySize*0.5f + 120.0f);
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
	createBuildings();

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
		hitsDetectionBuildings();
		VictoryCheck();
		FailCheck();
		drawGame();
		if (finish) break; //End of game
	}
}
