#include "ResourceManager.hpp"
#include "cstring"


sf::Texture ResourceManager::getRes(Types type)
{
	auto temp = resourcesMap.find(type);
	if (temp != resourcesMap.end()) return resourcesMap[type];
	else
	{
		sf::Texture texture;
		texture.loadFromFile(std::to_string((int)type));
		resourcesMap[type] = texture;
		return texture;
	}
}

ResourceManager::~ResourceManager()
{
	resourcesMap.clear();
}
