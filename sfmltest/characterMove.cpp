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

	SetCurrentDirectoryA("F:\\dev\\sfmlgame\\sfmltest\\Resources\\");
	
	sf::Text text;
	sf::String sentence;
	sf::Font font;

	if (!font.loadFromFile("OpenSans-Italic.ttf"))
		printf("Can't load font!!");
	
	sf::Clock clock;

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
				std::cout << "Text entered!!" << std::endl;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		myPlayer.setTextureRect(sf::IntRect((int)(150 * source.x), 117 * source.y, 137, 117));


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

		window.draw(bgSprite);
		// Vertex array
		sf::VertexArray vArray(sf::PrimitiveType::Quads, 4);
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

		text.setFillColor(sf::Color::White);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold | sf::Text::Italic);
		
		window.draw(text);

		window.draw(myPlayer);
		window.display();
		window.clear();
	}


	return;
	
}