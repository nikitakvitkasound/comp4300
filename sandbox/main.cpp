#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void SetTextValues(sf::Text& text_to_set, const sf::Font& f, unsigned int size, const std::string& s, const sf::Color& color);

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Testing Event");
	
	sf::Font font;
	if (!font.loadFromFile("media/font/helvetica.ttf"))
	{
		return -1;
	}
	sf::Text text_mouse_pos_x;
	sf::Text text_mouse_pos_y;
	SetTextValues(text_mouse_pos_x, font, 14, "", sf::Color::White);
	SetTextValues(text_mouse_pos_y, font, 14, "", sf::Color::White);

	const std::string text_x{ "x: " };
	const std::string text_y{ "y: " };
	const float OFFSET_BY_5 { 5.0f };
	const float OFFSET_BY_15 { 15.0f }; 
	const float OFFSET_BY_20{ 20.0f };


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				std::cout << ">>> Closing . . . \n";
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				std::cout << "Key is pressed.\tSCANCODE: " << event.key.scancode << "\n";
			}
			if (event.type == sf::Event::MouseMoved)
			{
				text_mouse_pos_x.setString(text_x + std::to_string(event.mouseMove.x));
				text_mouse_pos_y.setString(text_y + std::to_string(event.mouseMove.y));
				text_mouse_pos_x.setPosition(static_cast<float>(event.mouseMove.x) + OFFSET_BY_15, static_cast<float>(event.mouseMove.y) + OFFSET_BY_5);
				text_mouse_pos_y.setPosition(static_cast<float>(event.mouseMove.x) + OFFSET_BY_15, static_cast<float>(event.mouseMove.y) + OFFSET_BY_20);
			}
		}

		window.clear(sf::Color::Black);

		window.draw(text_mouse_pos_x);
		window.draw(text_mouse_pos_y);

		window.display();
	}

	return 0;
}


// - - - - - Definition - - - - - //

void SetTextValues(sf::Text& text_to_set, const sf::Font& f, unsigned int size, const std::string& s, const sf::Color& color)
{
	text_to_set.setFont(f);
	text_to_set.setCharacterSize(size);
	text_to_set.setString(s);
	text_to_set.setFillColor(color);
}