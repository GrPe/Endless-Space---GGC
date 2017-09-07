#pragma once
#include <cstring>
#include <vector>
#include "SFML\Graphics.hpp"


class ResourceManager
{
private:
	sf::Texture* texturesTab; //Tab of textures using in game
	sf::Font font; //Font using to display all texts in game
	const unsigned int MAXAMOUNTOFTEXTURES = 11;

public:
	//Constructors
	explicit ResourceManager(); //Default constructor - i is amount of textures

	//Gets functions
	sf::Texture& getTexture(unsigned int x);
	sf::Font& getFont() { return font; };

	//Destructor
	~ResourceManager();
};