#include <iostream>
#include <string>
#include <array>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct RecShape
{
	sf::RectangleShape shape{};
	sf::Vector2f velo{};
};

int main()
{
	const unsigned int WINDOW_WIDTH{ 1280 };
	const unsigned int WINDOW_HEIGHT{ 720 };
	const std::string WINDOW_NAME{ "Assignment01_Shapes" };
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

	sf::RectangleShape shape_01{ sf::Vector2f{ 100.0f, 100.0f } };
	shape_01.setPosition(50.0f, 50.0f);
	shape_01.setFillColor(sf::Color::Red);
	sf::Vector2f velocity_01{ -1.0f, -2.0f };

	sf::RectangleShape shape_02{ sf::Vector2f{ 100.0f, 100.0f } };
	shape_02.setPosition(350.0f, 150.0f);
	shape_02.setFillColor(sf::Color::Green);
	sf::Vector2f velocity_02{ -1.0f, 2.0f };

	std::array<RecShape, 2> shapes{ {{shape_01, velocity_01}, {shape_02, velocity_02}} };
	//std::vector<RecShape> shapes{ {shape_01, velocity_01}, {shape_02, velocity_02} };

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

		window.clear();
		
		for (auto& shape : shapes)
		{
			if (shape.shape.getPosition().y < 0.0f || shape.shape.getPosition().y + shape.shape.getGlobalBounds().height > WINDOW_HEIGHT)
			{
				shape.velo.y *= -1.0f;
			}
			if (shape.shape.getPosition().x < 0.0f || shape.shape.getPosition().x + shape.shape.getGlobalBounds().width > WINDOW_WIDTH)
			{
				shape.velo.x *= -1.0f;
			}
			shape.shape.move(shape.velo * velocity_scale);
			window.draw(shape.shape);
		}

		window.display();
	}

	return 0;
}