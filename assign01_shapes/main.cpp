#include <iostream>
#include <string>
#include <array>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>




int main()
{
	const unsigned int WINDOW_WIDTH{ 1280 };
	const unsigned int WINDOW_HEIGHT{ 720 };
	const std::string WINDOW_NAME{ "Assignment01_Shapes" };
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

	sf::Font font;
	if (!font.loadFromFile("media/font/helvetica.ttf"))
	{
		std::cerr << "[ERROR]: Can't load the font, check path to the .ttf file!\n";
		return -1;
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setString("RRed");

	sf::RectangleShape rectangle_01{ sf::Vector2f{ 100.0f, 100.0f } };
	rectangle_01.setPosition(0.0f, 0.0f);
	rectangle_01.setFillColor(sf::Color::Red);
	sf::Vector2f velocity_01{ -1.0f, -2.0f };


	//sf::CircleShape circle_01{ 5.0f, 30 };
	//circle_01.setPosition(28.0f, 37.0f);
	//circle_01.setFillColor(sf::Color::Blue);
	//sf::Vector2f velocity_02{ 2.0f, -1.0f };

	
	//text.setPosition(circle_01.getPosition().x + (circle_01.getGlobalBounds().width - text.getGlobalBounds().width) * 0.5f, 
	//	circle_01.getPosition().y + (circle_01.getGlobalBounds().height * 0.5f - text.getGlobalBounds().height));
	
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

		//for (auto& shape : shapes)
		//{
		//	if (shape.shape.getPosition().x < 0.0f || shape.shape.getPosition().x + shape.shape.getGlobalBounds().width > WINDOW_WIDTH)
		//	{
		//		shape.velo.x *= -1.0f;
		//	}
		//	if (shape.shape.getPosition().y < 0.0f || shape.shape.getPosition().y + shape.shape.getGlobalBounds().height > WINDOW_HEIGHT)
		//	{
		//		shape.velo.y *= -1.0f;
		//	}
		//	shape.shape.move(shape.velo * velocity_scale);
		//	window.draw(shape.shape);
		//}

		if (rectangle_01.getPosition().x < 0.0f || rectangle_01.getPosition().x + rectangle_01.getGlobalBounds().width > WINDOW_WIDTH)
		{
			velocity_01.x *= -1.0f;
		}
		if (rectangle_01.getPosition().y < 0.0f || rectangle_01.getPosition().y + rectangle_01.getGlobalBounds().height > WINDOW_HEIGHT)
		{
			velocity_01.y *= -1.0f;
		}

		rectangle_01.move(velocity_01 * velocity_scale);

		text.setPosition(rectangle_01.getPosition().x + (rectangle_01.getGlobalBounds().width - text.getGlobalBounds().width) * 0.5f,
			rectangle_01.getPosition().y + (rectangle_01.getGlobalBounds().height * 0.5f - text.getGlobalBounds().height));

		window.draw(rectangle_01);
		window.draw(text);

		window.display();
	}

	return 0;
}