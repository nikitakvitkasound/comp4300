#include <string>

//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	unsigned int window_width{ 1280 };
	unsigned int window_height{ 720 };
	std::string window_name{ "Assignment01_Shapes" };
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), window_name);

	sf::CircleShape circle(25);
	circle.setPosition(50.0f, 50.0f);
	float velo_x{ 0.05f };
	float velo_y{ 0.01f };

	while (window.isOpen())
	{
		sf::Event event;
			
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		circle.setPosition(circle.getPosition().x + velo_x, circle.getPosition().y + velo_y);

		window.clear(sf::Color(0, 0, 0));
		window.draw(circle);
		window.display();

	}
	return 0;
}