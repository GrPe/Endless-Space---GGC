#include "ResourceManager.hpp"
#include "cstring"

ResourceManager::ResourceManager()
{
	texturesTab = new sf::Texture[MAXAMOUNTOFTEXTURES];
	texturesTab[0].loadFromFile("src/player.png");
	texturesTab[1].loadFromFile("src/bullet.png");
	texturesTab[2].loadFromFile("src/enemy1.png");
	texturesTab[3].loadFromFile("src/enemy2.png");
	texturesTab[4].loadFromFile("src/enemy3.png");
	texturesTab[5].loadFromFile("src/hp.png");
	texturesTab[6].loadFromFile("src/Buildings0.png");
	texturesTab[7].loadFromFile("src/Buildings1.png");
	texturesTab[8].loadFromFile("src/Buildings2.png");
	texturesTab[9].loadFromFile("src/Buildings3.png");
	texturesTab[10].loadFromFile("src/Buildings4.png");

	soundShotPlayer.loadFromFile("src/shot.ogg");

	font.loadFromFile("src/font.ttf");
}

sf::Texture& ResourceManager::getTexture(unsigned int x)
{
	if (x > MAXAMOUNTOFTEXTURES) return texturesTab[0];
	return texturesTab[x];
}

sf::SoundBuffer & ResourceManager::getSB()
{
	return soundShotPlayer;
}


ResourceManager::~ResourceManager()
{
	delete[] texturesTab;
}
