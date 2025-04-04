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

	float mouse_pos_x{};
	float mouse_pos_y{};

	sf::ConvexShape z_cleveland;
	z_cleveland.setPointCount(8);
	z_cleveland.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	z_cleveland.setPoint(1, sf::Vector2f(100.0f, 0.0f));
	z_cleveland.setPoint(2, sf::Vector2f(100.0f, 50.0f));
	z_cleveland.setPoint(3, sf::Vector2f(150.0f, 50.0f));
	z_cleveland.setPoint(4, sf::Vector2f(150.0f, 100.0f));
	z_cleveland.setPoint(5, sf::Vector2f(50.0f, 100.0f));
	z_cleveland.setPoint(6, sf::Vector2f(50.0f, 50.0f));
	z_cleveland.setPoint(7, sf::Vector2f(0.0f, 50.0f));

	z_cleveland.setOrigin(75.0f, 50.f);
	z_cleveland.scale(0.5f, 0.5f);
	z_cleveland.setPosition(300.0f, 200.0f);
	z_cleveland.setFillColor(sf::Color::Green);

	//
	//sf::ConvexShape z_rhode{ z_cleveland };

	//z_rhode.setPosition(400.0f, 200.f);
	//z_rhode.setFillColor(sf::Color::Yellow);

	sf::ConvexShape teewee;
	teewee.setPointCount(8);
	teewee.setPoint(0, sf::Vector2f(0.0f, 50.0f));
	teewee.setPoint(1, sf::Vector2f(50.0f, 50.0f));
	teewee.setPoint(2, sf::Vector2f(50.0f, 0.0f));
	teewee.setPoint(3, sf::Vector2f(100.0f, 0.0f));
	teewee.setPoint(4, sf::Vector2f(100.0f, 50.0f));
	teewee.setPoint(5, sf::Vector2f(150.0f, 50.0f));
	teewee.setPoint(6, sf::Vector2f(150.0f, 100.0f));
	teewee.setPoint(7, sf::Vector2f(0.0f, 100.0f));
	teewee.setOrigin(75.0f, 50.f);
	teewee.scale(0.5f, 0.5f);
	teewee.setPosition(200.0f, 200.0f);

	teewee.setFillColor(sf::Color::Red);

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
				mouse_pos_x = static_cast<float>(event.mouseMove.x);
				mouse_pos_y = static_cast<float>(event.mouseMove.y);

				if (mouse_pos_x > WIN_WIDTH * FLIP_TEXT_MOUSE_COEFF && mouse_pos_y > WIN_HEIGHT * FLIP_TEXT_MOUSE_COEFF)
				{
					text_mouse_pos_x.setPosition(mouse_pos_x - OFFSET_BY_40, mouse_pos_y - OFFSET_BY_20);
					text_mouse_pos_y.setPosition(mouse_pos_x - OFFSET_BY_40, mouse_pos_y - OFFSET_BY_40);
				}
				else if (mouse_pos_x > WIN_WIDTH * FLIP_TEXT_MOUSE_COEFF)
				{
					text_mouse_pos_x.setPosition(mouse_pos_x - OFFSET_BY_40, mouse_pos_y + OFFSET_BY_5);
					text_mouse_pos_y.setPosition(mouse_pos_x - OFFSET_BY_40, mouse_pos_y + OFFSET_BY_20);
				}
				else if (mouse_pos_y > WIN_HEIGHT * FLIP_TEXT_MOUSE_COEFF)
				{
					text_mouse_pos_x.setPosition(mouse_pos_x + OFFSET_BY_15, mouse_pos_y - OFFSET_BY_20);
					text_mouse_pos_y.setPosition(mouse_pos_x + OFFSET_BY_15, mouse_pos_y - OFFSET_BY_40);
				}
				else
				{
					text_mouse_pos_x.setPosition(mouse_pos_x + OFFSET_BY_15, mouse_pos_y + OFFSET_BY_5);
					text_mouse_pos_y.setPosition(mouse_pos_x + OFFSET_BY_15, mouse_pos_y + OFFSET_BY_20);
				}

				text_mouse_pos_x.setString(text_pre_pos_x + std::to_string(event.mouseMove.x)); // std::to_string(mouse_pos_x) leads to .0000000 precision
				text_mouse_pos_y.setString(text_pre_pos_y + std::to_string(event.mouseMove.y));

			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				std::cout << "Rotate!\n";
				teewee.rotate(90);
			}
		}

		window.clear(sf::Color::Black);

		window.draw(teewee);
		window.draw(z_cleveland);
		//window.draw(z_rhode);
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