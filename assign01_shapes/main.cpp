#include <iostream>
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

	sf::Keyboard::Key input_up{ sf::Keyboard::W };
	sf::Keyboard::Key input_left{ sf::Keyboard::A };
	sf::Keyboard::Key input_down{ sf::Keyboard::S };
	sf::Keyboard::Key input_right{ sf::Keyboard::D };



	sf::RectangleShape shape_01{ sf::Vector2f{ 25.0f, 25.0f } };
	shape_01.setPosition(50.0f, 50.0f);
	shape_01.rotate(45);
	
	sf::RectangleShape shape_02{ sf::Vector2f{ 25.0f, 25.0f } };
	shape_02.setPosition(250.0f, 175.0f);
	shape_02.setFillColor(sf::Color::Red);
	
	
	float velo_x{ 10.0f };
	float velo_y{ 10.0f };


	while (window.isOpen())
	{
		sf::Event event;
			
		window.clear(sf::Color(0, 0, 0));
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == input_up)
				{
					shape_01.setPosition(shape_01.getPosition().x, shape_01.getPosition().y - velo_y);
					std::cout << "Up\n";
				}
				if (event.key.code == input_left) 
				{
					shape_01.setPosition(shape_01.getPosition().x - velo_x, shape_01.getPosition().y);
					std::cout << "Left!\n";
				}
				if (event.key.code == input_down)
				{
					shape_01.setPosition(shape_01.getPosition().x, shape_01.getPosition().y + velo_y);
					std::cout << "Down!\n";
				}
				if (event.key.code == input_right)
				{
					shape_01.setPosition(shape_01.getPosition().x + velo_x, shape_01.getPosition().y);
					std::cout << "Right!\n";
				}
				if (shape_01.getGlobalBounds().intersects(shape_02.getGlobalBounds()))
				{
					std::cout << "Hit!";
				}
				std::cout << shape_01.getPosition().x << ' ' << shape_01.getPosition().y << '\n';
			}
		}

		window.draw(shape_01);
		window.draw(shape_02);
		window.display();

	}
	return 0;
}