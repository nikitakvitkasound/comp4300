#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	const unsigned int WINDOW_WIDTH{ 1280 };
	const unsigned int WINDOW_HEIGHT{ 720 };
	const std::string WINDOW_NAME{ "Assignment01_Shapes" };
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

	sf::RectangleShape shape_01{ sf::Vector2f{ 100.0f, 100.0f } };
	shape_01.setPosition(50.0f, 50.0f);

	sf::Vector2f velocity{ -1.0f, -2.0f };
	float velocity_scale{ 0.05f };

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

		if (shape_01.getPosition().y < 0.0f || shape_01.getPosition().y + shape_01.getGlobalBounds().height > WINDOW_HEIGHT)
		{
			velocity.y *= -1.0f;
		}
		if (shape_01.getPosition().x < 0.0f || shape_01.getPosition().x + shape_01.getGlobalBounds().width > WINDOW_WIDTH)
		{
			velocity.x *= -1.0f;
		}

		shape_01.move(velocity * velocity_scale);

		// Render
		window.clear();
		window.draw(shape_01);
		window.display();
	}

	return 0;
}