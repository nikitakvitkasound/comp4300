#include <iostream>
#include <fstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

static sf::Vector2f getTextCenter(const sf::Text& text);
void checkCollisionWindowBoarder(const sf::RenderWindow& window, const sf::Shape& shape, sf::Vector2f& movement_vector);

struct Circle
{
	sf::Text name{};
	sf::CircleShape shape{};
	sf::Vector2f velocity{};
	float scale{120.0f};
};

struct Rectangle
{
	sf::Text name{};
	sf::RectangleShape shape{};
	sf::Vector2f velocity{};
	float scale{120.0f};
};



int main()
{
	const std::string CONFIG_FILE{ "media/config/config_shapes.txt" };
	
	std::ifstream fin(CONFIG_FILE);
	if (!fin)
	{
		std::cerr << "Can't Open File at: " << CONFIG_FILE << "\n";
		return -1;
	}

	// Window and Color
	unsigned int window_width{};
	unsigned int window_height{};
	std::string window_name{};
	
	// Color
	unsigned int color_r{};
	unsigned int color_g{};
	unsigned int color_b{};

	// Font
	sf::Font font;
	std::string font_file{};
	unsigned int font_size{};
	sf::Color font_color{};
	
	// Shapes
	std::string shape_name{};
	sf::Vector2f shape_position{};
	sf::Vector2f shape_velocity{};
	
	Circle circle;
	float circle_radius{};
	std::vector<Circle> circles;

	Rectangle rectangle;
	sf::Vector2f rectangle_size{};
	std::vector<Rectangle> rectangles;
	
	// Parse file
	std::string line{};
	while (fin >> line)
	{
		switch (line[0])
		{
		case('W'):
			fin >> window_width;
			fin >> window_height;
			fin >> window_name;
			break;
		
		case('F'):
			fin >> font_file;
			if (!font.loadFromFile(font_file))
			{
				std::cerr << "Can't Load Font File at: " << font_file << "\n";
				return -1;
			}
			fin >> font_size;			
			fin >> color_r;
			fin >> color_g;
			fin >> color_b;
			font_color = { static_cast<sf::Uint8>(color_r), static_cast<sf::Uint8>(color_g), static_cast<sf::Uint8>(color_b) };
			break;
		
		case('C'):
			fin >> shape_name;
			circle.name.setString(shape_name);
			circle.name.setFont(font);
			circle.name.setCharacterSize(font_size);
			circle.name.setOrigin(getTextCenter(circle.name));

			fin >> shape_position.x;
			fin >> shape_position.y;
			circle.shape.setPosition(shape_position.x, shape_position.y);
			
			fin >> shape_velocity.x;
			fin >> shape_velocity.y;
			circle.velocity = { shape_velocity.x, shape_velocity.y };

			fin >> color_r;
			fin >> color_g;
			fin >> color_b;
			circle.shape.setFillColor({ static_cast<sf::Uint8>(color_r), static_cast<sf::Uint8>(color_g), static_cast<sf::Uint8>(color_b) });
			
			fin >> circle_radius;
			circle.shape.setRadius(circle_radius);

			circles.push_back(circle);
			break;
		
		case('R'):
			fin >> shape_name;
			rectangle.name.setString(shape_name);
			rectangle.name.setFont(font);
			rectangle.name.setCharacterSize(font_size);
			rectangle.name.setOrigin(getTextCenter(rectangle.name));

			fin >> shape_position.x;
			fin >> shape_position.y;
			rectangle.shape.setPosition(shape_position.x, shape_position.y);

			fin >> shape_velocity.x;
			fin >> shape_velocity.y;
			rectangle.velocity = { shape_velocity.x, shape_velocity.y };

			fin >> color_r;
			fin >> color_g;
			fin >> color_b;
			rectangle.shape.setFillColor({ static_cast<sf::Uint8>(color_r), static_cast<sf::Uint8>(color_g), static_cast<sf::Uint8>(color_b) });

			fin >> rectangle_size.x;
			fin >> rectangle_size.y;
			rectangle.shape.setSize(rectangle_size);
			std::cout << circle_radius << '*';

			rectangles.push_back(rectangle);
			break;

		default:
			break;
		}
	}
	
	sf::RenderWindow window{ sf::VideoMode(window_width, window_height), window_name };
	sf::Clock clock;
	float dt{};

	while (window.isOpen()) {
		sf::Event event;
		dt = clock.restart().asSeconds();

		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		
		window.clear();	
		for (auto& c : circles)
		{
			c.shape.move(c.velocity * dt * c.scale);
			c.name.setPosition(c.shape.getPosition() + c.shape.getGlobalBounds().getSize() * 0.5f);
			checkCollisionWindowBoarder(window, c.shape, c.velocity);
			
			window.draw(c.shape);
			window.draw(c.name);
		}
		for (auto& r : rectangles)
		{
			r.shape.move(r.velocity * dt * r.scale);
			r.name.setPosition(r.shape.getPosition() + r.shape.getGlobalBounds().getSize() * 0.5f);
			checkCollisionWindowBoarder(window, r.shape, r.velocity);

			window.draw(r.shape);
			window.draw(r.name);
		}
		window.display();
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