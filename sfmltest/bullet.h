#pragma once
#include <SFML/Graphics.hpp>
#include "gameLoop.h"

// This class represents a single bullet 
class SingleBullet : public sf::Sprite 
{
public:
	SingleBullet();
	void setBulletPosition(sf::Vector2f intitialPosition, direction dir);			//Set initial position of bullet
	sf::Vector2f getBulletPosition();	//Get bullet's current position
	sf::Vector2f setDirection(direction dir);	//Determine direction
	void setBulletTexture(sf::Texture &bulletTexture);		//Set the texture 
	void setBulletTextureRect(sf::IntRect bulletRect);	//Set the texture Rectangle to choose the bullet type
	void destroyBullet();		//Delete bullet object
	void moveBullet(sf::Vector2i screenRes);			//Move bullet across screen
	void drawBullet();			//Draw the bullet
	void setBulletShot(bool value);
	bool isBulletShot();		//Return true if bullet has been shot
	sf::Sprite& getSprite();

private:
	sf::Sprite bulletSprite;
	sf::Vector2f bulletDirection;
	bool bulletShot;
};

// This class handles all bullet related operations
class Bullet : public sf::Sprite
{
public:
	Bullet();
	Bullet(char path[]);
	bool loadBulletImage();

private:
	std::vector <SingleBullet> bulletVector;
	char imageLocation[MAX_PATH];
	sf::Texture bulletTexture;
	SingleBullet singleBullet;
	bool bulletShot;
};
