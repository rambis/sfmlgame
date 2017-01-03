#include <SFML/Graphics.hpp>
#include <windows.h>
#include <stdio.h>
#include <string>
#include "globalHeader.h"

void basicGameLoop() // Just basic events using keyboards and mouse
{
	float rad = 50.f;	// Radius of circle
	float xPos = 0;		// X-coordinates of circle
	float yPos = 0;		// Y-coordinates of circle

	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!"); // Opens a windows of size 500 x 500 

	sf::Event event;

	// Get working directory to load resources from
	char path[MAX_PATH], picPath[MAX_PATH], fontPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	GetCurrentDirectoryA(MAX_PATH, picPath);
	strcat_s(path, "\\Resources\\"); // Look for resources in the ...../Resources/ folder
	strcpy_s(picPath, path);
	strcat_s(picPath, "skyTxt.jpg"); // Picture name in resources folder
	strcpy_s(fontPath, path);
	strcat_s(fontPath, "OpenSans-Bold.ttf"); // Font name in resources folder

	sf::Texture texture; 

	// Check if texture loaded properly.
	if (!texture.loadFromFile(picPath)) {
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			sf::Text text;
			sf::Font font;

			// Check font load
			if (!font.loadFromFile(fontPath))
				return;
			text.setFont(font);
			text.setString("Error loading picture");
			text.setFillColor(sf::Color::Black);
			text.setCharacterSize(40);

			window.clear(sf::Color::White);
			window.draw(text);
			window.display();
		}
	}
	
	//Create sprite and give it texture
	sf::Sprite sprite;
	sprite.setTexture(texture);
	texture.setSmooth(true);

	sf::Sprite sprite2;
	sprite2.setTexture(texture);
	sprite2.setTextureRect(sf::IntRect(200, 200, 200, 200));
	sprite2.setPosition(sf::Vector2f(300, 300));

	// Create an object of circleshape
	sf::CircleShape shape(rad); 
	shape.setTexture(&texture);
	shape.setFillColor(sf::Color(255, 0, 0, 255));

	// Below creates text 
	sf::Text text;
	sf::Font font;

	if (!font.loadFromFile(fontPath))
		return;
	text.setFont(font);
	text.setString("Error loading picture");
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(40);

	//window.setKeyRepeatEnabled(false); // Used to implement key de-bouncing

	while (window.isOpen()) // Main 'game' loop as it's called
	{


		sprite.scale(sf::Vector2f(0.1f, 0.1f));
		//sprite.setTextureRect(sf::IntRect(50, 50, 200, 200));


		while (window.pollEvent(event)) // Poll event. Don't use this for real-time games. It isn't good for realtime applications. Just testing here.
		{
			if (event.type == sf::Event::Closed)
				window.close();

			switch (event.type) // event.type reads what even was just performed on the window
			{
			case sf::Event::KeyPressed:	// Check if any key is pressed 
				if (event.key.code == sf::Keyboard::Return) // event.key.code is the code of the key pressed.
					shape.setRadius(rad++);
				else if (event.key.code == sf::Keyboard::RShift)	// Use sf::Keyboard for realtime polling of any keypressed or anything.
					shape.setRadius(rad--);
				else if (event.key.code == sf::Keyboard::Right)
					shape.setPosition(xPos++, yPos);
				else if (event.key.code == sf::Keyboard::Left)
					shape.setPosition(xPos--, yPos);
				else if (event.key.code == sf::Keyboard::Up)
					shape.setPosition(xPos, yPos--);
				else if (event.key.code == sf::Keyboard::Down)
					shape.setPosition(xPos, yPos++);
				break;

			case sf::Event::MouseButtonPressed:	// Mouse button pressed?
				if (event.key.code == sf::Mouse::Left)
				{
					sf::Vector2i k = sf::Mouse::getPosition(window);	// getPositon returns an object of Verctor2i class. It's basic structure is (x, y) like a pair.
					xPos = k.x - rad;
					yPos = k.y - rad;
				
					shape.setPosition(xPos, yPos); //set position of circle on screen.
				}
				break;

			case sf::Event::MouseWheelScrolled: // Mouse wheel scrolled
				if (event.key.code == sf::Mouse::VerticalWheel) // Generally vertical wheel used.
				{
					rad = rad + event.mouseWheelScroll.delta;	// delta is the number of ticks your scrollwheel does.
					xPos = xPos - event.mouseWheelScroll.delta;
					yPos = yPos - event.mouseWheelScroll.delta;
					shape.setRadius(rad);
					shape.setPosition(xPos, yPos);
				}
				break;
			}
		}

		if (rad >= 600)
			rad = 0;


		window.clear();	// Always required in a game loop. Otherwise, pixels from previous frame will remain on the screen.

		// Multiple draws draw to the back buffer. Display calls all the drawn stuff
		window.draw(sprite); 
		window.draw(sprite2);
		window.draw(text);
		window.draw(shape);

		window.display(); // Reads from the hidden buffer and displays onto screen
	}
}