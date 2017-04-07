#include "bullet.h"
#include <windows.h>
#include <string>

//******************************************************************
// Single Bullet Class method definitions
//******************************************************************
SingleBullet::SingleBullet()
{
	bulletShot = false;
	bulletDirection = sf::Vector2f(0, 0);
}

void SingleBullet::setBulletPosition(sf::Vector2f pos, direction dir)
{
	int xPosition, yPosition;
	if (dir == UP) {
		xPosition = pos.x + 58;
		yPosition = pos.y + 40;
	}	
	if (dir == DOWN) {
		xPosition = pos.x + 52;
		yPosition = pos.y + 105;
	}
	if (dir == LEFT) {
		xPosition = pos.x + 16;
		yPosition = pos.y + 80;
	}
	if (dir == RIGHT) {
		xPosition = pos.x + 100;
		yPosition = pos.y + 80;
	}
	bulletSprite.setPosition(xPosition, yPosition);
}

sf::Vector2f SingleBullet::getBulletPosition()
{
	return bulletSprite.getPosition();
}

sf::Vector2f SingleBullet::setDirection(direction dir)
{
	if (dir == UP) {
		bulletDirection = sf::Vector2f(0, -2);
	}
	else if (dir == DOWN) {
		bulletDirection = sf::Vector2f(0, 2);
	}
	else if (dir == LEFT) {
		bulletDirection = sf::Vector2f(-2, 0);
	}
	else if (dir == RIGHT) {
		bulletDirection = sf::Vector2f(2, 0);
	}
	return bulletDirection;
}

void SingleBullet::setBulletTexture(sf::Texture &bulletTexture)
{
	bulletSprite.setTexture(bulletTexture);
}

void SingleBullet::setBulletTextureRect(sf::IntRect bulletRect)
{
	bulletSprite.setTextureRect(bulletRect);
}

void SingleBullet::moveBullet(sf::Vector2i screenRes)
{
	bulletSprite.move(bulletDirection);
	int bulletXPosition = bulletSprite.getPosition().x;
	int bulletYPosition = bulletSprite.getPosition().y;
	if (bulletXPosition > screenRes.x || bulletXPosition < 0 || bulletYPosition > screenRes.y || bulletYPosition < 0) {
		destroyBullet();
	}
}

void SingleBullet::setBulletShot(bool value)
{
	bulletShot = value;
}

bool SingleBullet::isBulletShot()
{
	return bulletShot;
}

void SingleBullet::destroyBullet()
{
	
}

sf::Sprite& SingleBullet::getSprite()
{
	return bulletSprite;
}

void SingleBullet::drawBullet()
{
	//window.draw(bulletSprite);
	// Should be handled by a window class?
}

//******************************************************************
// Bullet Class method definitions
//******************************************************************

Bullet::Bullet()
{
	bulletShot = false;
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\Resources\\testbullet.png");
	strcpy_s(imageLocation, path);
}

Bullet::Bullet(char path[])
{
	bulletShot = false;
	strcpy_s(imageLocation, path);
}

bool Bullet::loadBulletImage()
{
	if (!bulletTexture.loadFromFile(imageLocation)) {
		return false;
	}
	return true;
}