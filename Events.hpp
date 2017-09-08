#pragma once
#include "SFML\Graphics.hpp"
#include "Player.hpp"

class Events
{
public:
	explicit Events() {};
	void CatchEvent(sf::RenderWindow& window, Player& player, std::vector <Bullet>& vb, sf::Texture& tx);
	void WinEvent(sf::RenderWindow& window);
};