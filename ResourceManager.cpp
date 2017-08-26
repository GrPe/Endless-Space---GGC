#include "ResourceManager.hpp"
#include "cstring"
#include <algorithm>


sf::Texture& ResourceManager::getRes(std::string type)
{
	auto temp = texturesMap.find(type);
	if (temp != texturesMap.end()) return texturesMap[type];
	else
	{
		sf::Texture texture;
		texture.loadFromFile(("src/" + type + ".png"));
		texturesMap[type] = texture;
		return texturesMap[type];
	}
}

ResourceManager::~ResourceManager()
{
	texturesMap.clear();
}
