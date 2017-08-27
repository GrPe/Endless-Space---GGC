#pragma once
#include "SFML\Graphics.hpp"
#include "Player.hpp"

class Events
{
	//only static functions
private:
	bool pMoveLeft;
	bool pMoveRight;
	bool pShot;

public:
	explicit Events() {};
	void CatchEvent(sf::RenderWindow& window, Player& player);
};