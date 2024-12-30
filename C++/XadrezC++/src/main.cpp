#include <SFML/Graphics.hpp>
#include "../include/tabuleiro.hpp"
#include "../include/I_UI.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	Tabuleiro tabuleiro(100);
	I_UI<sf::VertexArray>* tabuleiroUI = &tabuleiro;

	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else break;
		}
		tabuleiroUI->draw(&window);
		window.display();
		sf::sleep(sf::seconds(1));
	}
	return 0;
}