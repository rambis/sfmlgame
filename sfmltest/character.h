#pragma once

#include <SFML/Graphics.hpp>
#include "gameLoop.h"

class Character : public sf::Sprite
{
public:
	Character();

/*	void setBulletPosition(sf::Vector2f intitialPosition, direction dir);			//Set initial position of bullet
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
	*/

private:
	sf::Sprite characterSprite;
	char imageLocation[MAX_PATH];
	sf::Vector2f bulletDirection;
	bool bulletShot;
};
