#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "globalHeader.h"
#include <stdlib.h> 

// Move character sprites across the screen
void characterMove() 
{
	enum direction {DOWN, UP, LEFT, RIGHT};

	sf::Vector2i source;
	sf::Vector2f position(0, 0); // Source -> keyboard input, position -> sprite position on window

//	sf::Vector2f screenRes((float)getScrRes.width, (float)getScrRes.height);

	sf::VideoMode videoMode(sf::VideoMode::getDesktopMode());
	sf::Vector2i screenRes;
	screenRes.x = videoMode.width;
	screenRes.y = videoMode.height;
	sf::RenderWindow window(videoMode, "HELLO!");

	sf::Event event;

	sf::Texture texture;
	sf::Texture bgTexture;
	sf::Texture bulletTexture;

	bgTexture.setRepeated(true);

	sf::Sprite myPlayer;
//	sf::Sprite bullet;
	sf::Sprite bgSprite;

	char path[MAX_PATH], playerImage[MAX_PATH], bgImage[MAX_PATH], bulletImage [MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\Resources\\");
	strcpy_s(playerImage, path);
	strcat_s(playerImage, "testSprite.png");
	strcpy_s(bgImage, path);
	strcat_s(bgImage, "grass2.jpg");
	strcpy_s(bulletImage, path);
	strcat_s(bulletImage, "bullets.png");

	if (!texture.loadFromFile(playerImage) || !bgTexture.loadFromFile(bgImage) || !bulletTexture.loadFromFile(bulletImage))
		exit(2);

	myPlayer.setTexture(texture);
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(sf::IntRect(0, 0, screenRes.x, screenRes.y));
	//bgSprite.
	bgTexture.setRepeated(true);



	SetCurrentDirectoryA("F:\\dev\\sfmlgame\\sfmltest\\Resources\\");
	
	sf::Text text;
	sf::String sentence;
	sf::Font font;

	if (!font.loadFromFile("OpenSans-Italic.ttf"))
		printf("Can't load font!!");
	
	sf::Clock clock;

	bool bulletShot = false;
	sf::Vector2f bulletSpeed(0, 0);

	std::vector <sf::Sprite> bulletVec;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode >= 32 && event.text.unicode <= 126)
					sentence += (char)event.text.unicode;

				else if (event.text.unicode == 8 && sentence.getSize() > 0)
					sentence.erase(sentence.getSize() - 1, 1);

				text.setString(sentence);
				//std::cout << "Text entered!!" << std::endl;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		
		myPlayer.setTextureRect(sf::IntRect((int)(150 * source.x), 117 * source.y, 137, 117));

		std::vector <sf::Sprite>::iterator it = bulletVec.begin();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			bulletShot = true;
			sf::Sprite bullet;
			bullet.setTexture(bulletTexture);
			bullet.setTextureRect(sf::IntRect(85, 72, 21, 22));

			if (source.y == RIGHT) {
				bullet.setPosition(sf::Vector2f(myPlayer.getPosition().x + 100, myPlayer.getPosition().y + 80));
				bulletSpeed = sf::Vector2f(2, 0);
			}
			else if (source.y == LEFT) {
				bullet.setPosition(sf::Vector2f(myPlayer.getPosition().x + 16, myPlayer.getPosition().y + 80));
				bulletSpeed = sf::Vector2f(-2, 0);
			}
			else if (source.y == UP) {
				bullet.setPosition(sf::Vector2f(myPlayer.getPosition().x + 58, myPlayer.getPosition().y + 40));
				bulletSpeed = sf::Vector2f(0, -2);
			}
			else if (source.y == DOWN) {
				bullet.setPosition(sf::Vector2f(myPlayer.getPosition().x + 52, myPlayer.getPosition().y + 105));
				bulletSpeed = sf::Vector2f(0, 2);
			}
			bulletVec.push_back(bullet);
		}

		it = bulletVec.begin();
		while (it != bulletVec.end()) {
			if (it->getPosition().x > 800 || it->getPosition().x < 0 || it->getPosition().y < 0 || it->getPosition().y > 800)
				it = bulletVec.erase(it);
			if (it == bulletVec.end())
				break;
			it++;
		}

		if (bulletVec.size() != 0) {
			it = bulletVec.begin();
			while (it != bulletVec.end()) {
				it->move(bulletSpeed);
				it++;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			source.y = DOWN;
			/*if (event.type == sf::Event::KeyPressed)
				position.y++;*/
			myPlayer.move(0, 1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			source.y = UP;
			/*if (event.type == sf::Event::KeyPressed)
				position.y--;*/
			myPlayer.move(0, -1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			source.y = LEFT;
			/*if (event.type == sf::Event::KeyPressed)
				position.x--;*/
			myPlayer.move(-1, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			source.y = RIGHT;
			/*if (event.type == sf::Event::KeyPressed)
				position.x++;*/
			myPlayer.move(1, 0);
		}

		sf::Time elapsed = clock.getElapsedTime();

	//	myPlayer.setPosition(position);

		if ((event.type == sf::Event::KeyPressed) & (elapsed.asMilliseconds() > 50))
		{
			source.x++;
			clock.restart();
		}
		
		if(event.type == sf::Event::KeyReleased)
			source.x = 0;

		if (source.x > 6)
			source.x = 0;

		//window.draw(bgSprite);
		// Vertex array
	/*	sf::VertexArray vArray(sf::PrimitiveType::Quads, 4);
		sf::Vector2i arrayBlockSize(20, 20);

		for (int i = 0; i < (screenRes.x / arrayBlockSize.x); i++)
		{
			for (int j = 0; j < screenRes.y / arrayBlockSize.y; j++)
			{
				vArray[0].position = sf::Vector2f(i * arrayBlockSize.x, j * arrayBlockSize.y);
				vArray[1].position = sf::Vector2f((i + 1)* arrayBlockSize.x, j * arrayBlockSize.y);
				vArray[2].position = sf::Vector2f((i + 1) * arrayBlockSize.x, (j + 1) * arrayBlockSize.y);
				vArray[3].position = sf::Vector2f(i * arrayBlockSize.x, (j + 1) * arrayBlockSize.y);

				for (int k = 0; k < 4; k++)
				{
					int red = rand() % 255;
					int green = rand() % 255;
					int blue = rand() % 255;

					vArray[k].color = sf::Color(red, green, blue, 127);
				}

				window.draw(vArray);
			}
		}
		*/
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold | sf::Text::Italic);
		
		window.draw(text);

		it = bulletVec.begin();
		while (it != bulletVec.end()) {
			window.draw(*it);
			it++;
		}
		window.draw(myPlayer);
		window.display();
		window.clear();
	}


	return;
	
}