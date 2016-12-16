#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::RenderWindow wind(sf::VideoMode(800, 900), "Haha Gotcha!");
	sf::CircleShape shape(50.f);
	shape.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				wind.clear();
				wind.draw(shape);
				wind.display();
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}