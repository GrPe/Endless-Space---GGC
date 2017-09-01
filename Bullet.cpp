#include "Bullet.hpp"

Bullet::Bullet(const float x,const float y,sf::Texture& tx, float s)
{
	sprite.setTexture(tx);
	sprite.setOrigin(tx.getSize().x*0.5f, tx.getSize().y*0.5f);
	sprite.setScale(0.5f, 0.5f);
	sprite.setPosition(x, y);
	speed = s;
}

sf::Sprite & Bullet::getSprite()
{
	return sprite;
}
