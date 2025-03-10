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

	float dt;
	sf::Clock dt_clock;

	sf::Keyboard::Key input_up{ sf::Keyboard::W };
	sf::Keyboard::Key input_left{ sf::Keyboard::A };
	sf::Keyboard::Key input_down{ sf::Keyboard::S };
	sf::Keyboard::Key input_right{ sf::Keyboard::D };



	sf::RectangleShape shape_01{ sf::Vector2f{ 100.0f, 100.0f } };
	shape_01.setPosition(50.0f, 50.0f);

	float movement_speed{ 100.0f };
	float scale_speed{ 5.0f };
	sf::Vector2f velocity;

	while (window.isOpen())
	{
		dt = dt_clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		velocity.x = 0.0f;
		velocity.y = 0.0f;
		if (sf::Keyboard::isKeyPressed(input_up))
		{
			velocity.y += -movement_speed * dt * scale_speed;
		}
		if (sf::Keyboard::isKeyPressed(input_left))
		{
			velocity.x += -movement_speed * dt * scale_speed;
		}
		if (sf::Keyboard::isKeyPressed(input_down))
		{
			velocity.y += movement_speed * dt * scale_speed;
		}
		if (sf::Keyboard::isKeyPressed(input_right))
		{
			velocity.x += movement_speed * dt * scale_speed;
		}
		shape_01.move(velocity);

		if (shape_01.getPosition().y < 0.0f)
		{
			shape_01.setPosition(shape_01.getPosition().x, 0.0f);
		}
		if (shape_01.getPosition().x < 0.0f)
		{
			shape_01.setPosition(0, shape_01.getPosition().y);
		}
		if (shape_01.getPosition().y + shape_01.getGlobalBounds().height > WINDOW_HEIGHT)
		{
			shape_01.setPosition(shape_01.getPosition().x, WINDOW_HEIGHT - shape_01.getGlobalBounds().height);
		}
		if (shape_01.getPosition().x + shape_01.getGlobalBounds().width > WINDOW_WIDTH)
		{
			shape_01.setPosition(WINDOW_WIDTH - shape_01.getGlobalBounds().width, shape_01.getPosition().y);
		}


		// Render

		window.clear();
		window.draw(shape_01);
		window.display();
	}

	return 0;
}