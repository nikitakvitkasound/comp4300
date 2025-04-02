#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

static sf::Vector2f getTextCenter(const sf::Text& text);

void checkCollisionWindowBoarder(const sf::RenderWindow& window, const sf::Shape& shape, sf::Vector2f& movement_vector);


int main()
{
	const unsigned int WINDOW_WIDTH{ 800 };
	const unsigned int WINDOW_HEIGHT{ 600 };
	const std::string WINDOW_NAME{ "Assignment 01: Shapes" };
	const std::string ADDRESS_FONT_FILE{ "media/font/helvetica.ttf" };


	sf::RenderWindow window{ sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME };
	window.setFramerateLimit(60);
	sf::Clock clock;
	float dt{};
	float velocity{ 300.0f };
	
	sf::Font font;
	if (!font.loadFromFile(ADDRESS_FONT_FILE))
	{
		std::cerr << "Can't Load Font File From: " << ADDRESS_FONT_FILE << "\n";
		return -1;
	}
	sf::Text text_01;
	text_01.setFont(font);
	text_01.setCharacterSize(36);
	text_01.setFillColor(sf::Color::Black);
	text_01.setString("Feed");
	text_01.setOrigin(getTextCenter(text_01));
	
	sf::RectangleShape rect_01{ {100.0f, 100.0f} };
	rect_01.setFillColor(sf::Color(219, 252, 208));
	rect_01.setPosition(400, 300);
	sf::Vector2f move_vector{ -0.70f, 0.5f };

	while (window.isOpen()) {
		//auto dt{ clock.restart().asSeconds() };
		sf::Event event;

		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		dt = clock.restart().asSeconds();
		//if (rect_01.getPosition().x < 0 || (rect_01.getPosition().x + rect_01.getGlobalBounds().width) > window.getView().getSize().x)
		//{
		//	move_vector.x *= -1;
		//}
		//if (rect_01.getPosition().y < 0 || (rect_01.getPosition().y + rect_01.getGlobalBounds().height) > window.getView().getSize().y)
		//{
		//	move_vector.y *= -1;
		//}
		checkCollisionWindowBoarder(window, rect_01, move_vector);

		rect_01.move(move_vector * dt * velocity);
		text_01.setPosition(rect_01.getPosition() + rect_01.getGlobalBounds().getSize() * 0.5f);


		window.clear(sf::Color(194, 178, 171));
		window.draw(rect_01);
		window.draw(text_01);

		window.display();
		//std::cout << "dt:: " << dt << '\n';
	}

	return 0;
}





// - - - - - Definition - - - - - //


static sf::Vector2f getTextCenter(const sf::Text& text)
{
	return { (text.getGlobalBounds().getSize() * 0.5f) + text.getLocalBounds().getPosition() };
}

void checkCollisionWindowBoarder(const sf::RenderWindow& window, const sf::Shape& shape, sf::Vector2f& movement_vector)
{
	if (shape.getPosition().x < 0 || (shape.getPosition().x + shape.getGlobalBounds().width) > window.getView().getSize().x)
	{
		movement_vector.x *= -1;
	}
	if (shape.getPosition().y < 0 || (shape.getPosition().y + shape.getGlobalBounds().height) > window.getView().getSize().y)
	{
		movement_vector.y *= -1;
	}
}