#include <iostream>
//#include <format>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>


int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Testing Event");
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				std::cout << event.key.code << " is pressed . . .\n";
			}
			if (event.type == sf::Event::Closed)
			{
				std::cout << "Closing . . . \n";
				window.close();
			}
			if (event.type == sf::Event::MouseMoved)
			{
				std::cout << "mouse x: " << event.mouseMove.x << "\n";
				std::cout << "mouse y: " << event.mouseMove.y << "\n";

			}
		}
	}

	return 0;
}