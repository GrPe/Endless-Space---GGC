#include "Emeny.hpp"

Enemy::Enemy(int _hp, float _speed, sf::Texture & texture) : SpaceShip(_hp, _speed, texture)
{
	sprite.setOrigin(texture.getSize().x*0.5f, texture.getSize().y*0.5f);
	sprite.setScale(0.4f, 0.4f);
}

void Enemy::shot(std::vector<Bullet>& listOfEnemyBullets, sf::Texture & tx)
{
	
}
