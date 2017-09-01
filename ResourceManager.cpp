#include "ResourceManager.hpp"
#include "cstring"

ResourceManager::ResourceManager(int i) : MAXAMOUNTOFTEXTURES(i)
{
	texturesTab = new sf::Texture[MAXAMOUNTOFTEXTURES];
	texturesTab[0].loadFromFile("src/player.png");
	texturesTab[1].loadFromFile("src/bullet.png");
}

sf::Texture& ResourceManager::getRes(unsigned int x)
{
	if (x > MAXAMOUNTOFTEXTURES) return texturesTab[0];
	return texturesTab[x];
}

ResourceManager::~ResourceManager()
{
	delete[] texturesTab;
}
