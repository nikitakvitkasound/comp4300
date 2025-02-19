#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void SetTextValues(sf::Text& text_to_set, const sf::Font& f, unsigned int size, const std::string& s, const sf::Color& color);

int main()
{
	const unsigned int WIN_WIDTH{ 800 };
	const unsigned int WIN_HEIGHT{ 600 };
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Testing Event");
	
	sf::Font font;
	if (!font.loadFromFile("media/font/helvetica.ttf"))
	{
		return -1;
	}
	sf::Text text_mouse_pos_x;
	sf::Text text_mouse_pos_y;
	SetTextValues(text_mouse_pos_x, font, 14, "", sf::Color::White);
	SetTextValues(text_mouse_pos_y, font, 14, "", sf::Color::White);

	const std::string text_pre_pos_x{ "x: " };
	const std::string text_pre_pos_y{ "y: " };
	const float OFFSET_BY_5 { 5.0f };
	const float OFFSET_BY_15 { 15.0f }; 
	const float OFFSET_BY_20{ 20.0f };
	const float OFFSET_BY_40{ 40.0f };
	const float FLIP_TEXT_MOUSE_COEFF{ 0.95f }; // 0.95 == passing 95% of screen width or height

	int mouse_pos_x{};
	int mouse_pos_y{};

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
				mouse_pos_x = event.mouseMove.x;
				mouse_pos_y = event.mouseMove.y;
				text_mouse_pos_x.setString(text_pre_pos_x + std::to_string(mouse_pos_x));
				text_mouse_pos_y.setString(text_pre_pos_y + std::to_string(mouse_pos_y));
				
				if (mouse_pos_x > WIN_WIDTH * FLIP_TEXT_MOUSE_COEFF && mouse_pos_y > WIN_HEIGHT * FLIP_TEXT_MOUSE_COEFF)
				{
					text_mouse_pos_x.setPosition(static_cast<float>(mouse_pos_x) - OFFSET_BY_40, static_cast<float>(mouse_pos_y) - OFFSET_BY_20);
					text_mouse_pos_y.setPosition(static_cast<float>(mouse_pos_x) - OFFSET_BY_40, static_cast<float>(mouse_pos_y) - OFFSET_BY_40);
				}
				else if (mouse_pos_x > WIN_WIDTH * FLIP_TEXT_MOUSE_COEFF)
				{
					text_mouse_pos_x.setPosition(static_cast<float>(mouse_pos_x) - OFFSET_BY_40, static_cast<float>(mouse_pos_y) + OFFSET_BY_5);
					text_mouse_pos_y.setPosition(static_cast<float>(mouse_pos_x) - OFFSET_BY_40, static_cast<float>(mouse_pos_y) + OFFSET_BY_20);
				}
				else if (mouse_pos_y > WIN_HEIGHT * FLIP_TEXT_MOUSE_COEFF)
				{
					text_mouse_pos_x.setPosition(static_cast<float>(mouse_pos_x) + OFFSET_BY_15, static_cast<float>(mouse_pos_y) - OFFSET_BY_20);
					text_mouse_pos_y.setPosition(static_cast<float>(mouse_pos_x) + OFFSET_BY_15, static_cast<float>(mouse_pos_y) - OFFSET_BY_40);
				}
				else
				{
					text_mouse_pos_x.setPosition(static_cast<float>(mouse_pos_x) + OFFSET_BY_15, static_cast<float>(mouse_pos_y) + OFFSET_BY_5);
					text_mouse_pos_y.setPosition(static_cast<float>(mouse_pos_x) + OFFSET_BY_15, static_cast<float>(mouse_pos_y) + OFFSET_BY_20);
				}
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