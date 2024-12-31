#include <SFML/Graphics.hpp>
#include "../include/tabuleiro.hpp"
#include "../include/I_UI.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "XADREZ", sf::Style::Titlebar | sf::Style::Close);
	int tamanho_casas = 100;
	Tabuleiro tabuleiro(tamanho_casas, true);
	I_UI<sf::VertexArray>* tabuleiroUI = &tabuleiro;

	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::Black);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				int pos_x = (int)(event.mouseButton.x/tamanho_casas), pos_y = (int)(event.mouseButton.y/tamanho_casas);
				while (event.mouseButton.button == sf::Mouse::Right)
				{
					window.clear(sf::Color::Black);
					tabuleiro.newPosObject(pos_x, pos_y, {(float)event.mouseButton.x, (float)event.mouseButton.y}, true);
					tabuleiroUI->draw(&window);
					window.display();
					sf::sleep(sf::seconds(1));
				}
			}
		}
		tabuleiroUI->draw(&window);
		window.display();
		sf::sleep(sf::seconds(1));
	}
	return 0;
}