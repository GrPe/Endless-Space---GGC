#include "ResourceManager.hpp"
#include "cstring"

ResourceManager::ResourceManager()
{
	texturesTab = new sf::Texture[1];
	texturesTab[0].loadFromFile("src/player.png");
}

sf::Texture& ResourceManager::getRes(int x)
{
	return texturesTab[0];
}

ResourceManager::~ResourceManager()
{
	delete[] texturesTab;
}
