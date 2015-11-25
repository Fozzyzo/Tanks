#include "SFML\Graphics.hpp"

int main()
{
		sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
		sf::Texture texture;
		if (!texture.loadFromFile("TankBottom.png"));
		
		sf::RectangleShape line(sf::Vector2f(10, 2));
		line.setPosition(100, 400);

		sf::Sprite player1(texture);
		player1.setPosition(100, 400);
		sf::Sprite player2(texture);
		player2.setPosition(700, 400);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear(sf::Color(255,255,255));
			window.draw(line);
			window.draw(player1);
			window.draw(player2);
			window.display();
		}
}
