#include <SFML/Graphics.hpp>
#include "globalHeader.h"

void keyMouseEvents(sf::RenderWindow window, sf::Event event, sf::CircleShape &shape) // Just basic events using keyboards and mouse
{
	float rad = 50.f;	// Radius of circle
	float xPos = 0;		// X-coordinates of circle
	float yPos = 0;		// Y-coordinates of circle

	while (window.pollEvent(event)) // Poll event. Don't use this for real-time games. It isn't good for realtime applications. Just testing here.
	{
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
}