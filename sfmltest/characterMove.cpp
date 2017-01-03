#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "globalHeader.h"

// Move character sprites across the screen
void characterMove() 
{
	enum direction {DOWN, UP, LEFT, RIGHT};

	sf::Vector2i source;
	sf::Vector2f position(0, 0); // Source -> keyboard input, position -> sprite position on window

	sf::VideoMode getScrRes = sf::VideoMode::getDesktopMode();

	sf::Vector2f screenRes((float)getScrRes.width, (float)getScrRes.height);

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "HELLO!");

	sf::Event event;

	sf::Texture texture;
	sf::Texture bgTexture;

	bgTexture.setRepeated(true);

	sf::Sprite myPlayer;
	sf::Sprite bgSprite;

	char path[MAX_PATH], spriteImage[MAX_PATH], bgImage[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\Resources\\");
	strcpy_s(spriteImage, path);
	strcat_s(spriteImage, "testSprite.png");
	strcpy_s(bgImage, path);
	strcat_s(bgImage, "skyTxt.jpg");

	if (!texture.loadFromFile(spriteImage) || !bgTexture.loadFromFile(bgImage))
		exit(2);

	myPlayer.setTexture(texture);
	bgSprite.setTexture(bgTexture);
//	bgSprite.setTextureRect(sf::IntRect(0, 0, screenRes.x, screenRes.y));
	

	
	sf::Clock clock;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		myPlayer.setTextureRect(sf::IntRect((int)(150 * source.x), 117 * source.y, 137, 117));


		switch (event.key.code)
		{
		case sf::Keyboard::Down:
			source.y = DOWN;
			if (event.type == sf::Event::KeyPressed)
				position.y++;
			break;

		case sf::Keyboard::Up:
			source.y = UP;
			if (event.type == sf::Event::KeyPressed)
				position.y--;
			break;

		case sf::Keyboard::Left:
			source.y = LEFT;
			if (event.type == sf::Event::KeyPressed)
				position.x--;
			break;

		case sf::Keyboard::Right:
			source.y = RIGHT;
			if (event.type == sf::Event::KeyPressed)
				position.x++;
			break;
		}

		sf::Time elapsed = clock.getElapsedTime();

		myPlayer.setPosition(position);

		if ((event.type == sf::Event::KeyPressed) & (elapsed.asMilliseconds() % 500 == 0))
			source.x++;
		else
			source.x = 0;

		if (source.x > 6)
			source.x = 0;

		window.clear();
		window.draw(bgSprite);
		window.draw(myPlayer);
		window.display();
	}


	return;
	
}