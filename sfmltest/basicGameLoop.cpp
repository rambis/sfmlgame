#include <SFML/Graphics.hpp>
#include "globalHeader.h"

void basicGameLoop() // Just basic events using keyboards and mouse
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!"); // Opens a windows of size 500 x 500 

	float rad = 50.f;	// Radius of circle
	float xPos = 0;		// X-coordinates of circle
	float yPos = 0;		// Y-coordinates of circle

	sf::CircleShape shape(rad); // create an object of circleshape
	shape.setFillColor(sf::Color::Blue);

	//window.setKeyRepeatEnabled(false); // Used to implement key de-bouncing

	while (window.isOpen()) // Main 'game' loop as it's called
	{
		sf::Event event;

		keyMouseEvents(window, event, shape);

		while (window.pollEvent(event)) 
		{
			if (sf::Event::Closed)
				window.close();
		}

		

		if (rad >= 600)
			rad = 0;

		window.clear();	// Always required in a game loop. Otherwise, pixels from previous frame will remain on the screen.
		window.draw(shape); // Drawing basically puts all the pixels into a hidden buffer behind the scenes
		window.display(); // Reads from the hidden buffer and displays onto screen
	}
}