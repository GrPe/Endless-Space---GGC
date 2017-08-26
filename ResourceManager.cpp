#include "ResourceManager.hpp"
#include "cstring"

sf::Texture& ResourceManager::getRes(std::string type)
{
	auto temp = texturesMap.find(type);
	if (temp != texturesMap.end()) return texturesMap[type];
	sf::Texture texture;
	std::string tempstring = "src/" + type + ".png";
	texture.loadFromFile((tempstring));
	texturesMap.insert(std::pair<std::string, sf::Texture>(type, texture));
	return texturesMap[type];
}

ResourceManager::~ResourceManager()
{
	texturesMap.clear();
}
