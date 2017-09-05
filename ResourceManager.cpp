#include "ResourceManager.hpp"
#include "cstring"

ResourceManager::ResourceManager(int i) : MAXAMOUNTOFTEXTURES(i)
{
	texturesTab = new sf::Texture[MAXAMOUNTOFTEXTURES];
	texturesTab[0].loadFromFile("src/player.png");
	texturesTab[1].loadFromFile("src/bullet.png");
	texturesTab[2].loadFromFile("src/enemy1.png");
	texturesTab[3].loadFromFile("src/enemy2.png");
	texturesTab[4].loadFromFile("src/enemy3.png");
	font.loadFromFile("src/font.ttf");
}

sf::Texture& ResourceManager::getTexture(unsigned int x)
{
	if (x > MAXAMOUNTOFTEXTURES) return texturesTab[0];
	return texturesTab[x];
}

ResourceManager::~ResourceManager()
{
	delete[] texturesTab;
}
