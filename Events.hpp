#pragma once
#include "SFML\Graphics.hpp"

class Events
{
	//only static functions
private:
	static bool pMoveLeft;
	static bool pMoveRight;
	static bool pShot;

public:
	explicit Events() {};
	static void CatchEvent(sf::RenderWindow& window);
};