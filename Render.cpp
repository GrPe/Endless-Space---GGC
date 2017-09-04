#include "Render.hpp"

void Render::draw()
{
	window.clear();
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

void Render::moveObjects()
{
	//bullets
	for (auto& x : bulletsVector) x.move();
	for (auto& x : bulletsEnemyVector) x.move();
	//aliens
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

void Render::check()
{
	std::vector<std::vector<Bullet>::iterator> tempBulletVector; //stores id of unused bullets;
	std::vector<std::list<Bullet>::iterator> tempBulletList; //stores id of unused enemy's bullets
	
	//Enemy Movement -- Collision
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

	//Enemy shooting
	enemyShoot();

	//Hits detection (enemies)
	std::vector<std::vector<Enemy>::iterator> deadEnemies;
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
  				tempBulletVector.push_back(bullet);
			}
		}
	}

	//Player bullets
	for (auto x = bulletsVector.begin(); x != bulletsVector.end(); x++)
	{
		if (x->getSprite().getPosition().y < 0) tempBulletVector.push_back(x);
	}
	for (auto x : tempBulletVector) bulletsVector.erase(x);
	tempBulletVector.clear();

	//Enemy bullets
	for (auto x = bulletsEnemyVector.begin(); x != bulletsEnemyVector.end(); x++)
	{
		if (x->getSprite().getPosition().y > ySize) tempBulletList.push_back(x);
	}
	for (auto x : tempBulletList) bulletsEnemyVector.erase(x);
	tempBulletList.clear();

	//Hits detection (player)
	{
		float playerXMinPosition = player.getSprite().getPosition().x - player.getSprite().getTexture()->getSize().x*0.2f;
		float playerXMaxPosition = player.getSprite().getPosition().x + player.getSprite().getTexture()->getSize().x*0.2f;
		for (auto bullet = bulletsEnemyVector.begin(); bullet != bulletsEnemyVector.end(); bullet++)
		{
			float bulletXPosition = bullet->getSprite().getPosition().x;
			float bulletYPosition = bullet->getSprite().getPosition().y;
			if (bulletYPosition >= player.getSprite().getPosition().y)
			{
				if (bulletXPosition > playerXMinPosition && bulletXPosition < playerXMaxPosition); //failure();
			}
		}
	}

	//Destroy enemies
	//Not Finish YET!
	for (auto& x : deadEnemies) alienArmyVector.erase(x);
	deadEnemies.clear();

}

void Render::enemyShoot()
{
	if (getIntFromRange(1, 100) % 5 == 0) // Amount of enemy's bullets
	{
		int temp = getIntFromRange(0, alienArmyVector.size() - 1);
		alienArmyVector[temp].shot(bulletsEnemyVector, rs.getRes(1));
	}
}

int Render::getIntFromRange(int from, int to)
{
	std::uniform_int_distribution<int> distribution(from,to);
	return distribution(generator);
}

Render::Render(int x, int y) : xSize(x), ySize(y), window(sf::VideoMode(xSize, ySize),
	"Endless Space"), rs(10) 
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
	for (unsigned int i = 0; i < amountOfEnemies; i++) alienArmyVector.push_back(Enemy(1, 180.0f, rs.getRes(getIntFromRange(2,4))));
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

	//start movement of enemies
	isMovingRight = true;
	
	//main loop of game
	while (window.isOpen())
	{
		events.CatchEvent(window,player, bulletsVector,rs.getRes(1));
		moveObjects();
		check();
		draw();
	}
}
