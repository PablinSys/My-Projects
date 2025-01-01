#include <SFML/Graphics.hpp>
#include "../include/tabuleiro.hpp"
#include "../include/I_UI.hpp"
#include <iostream>


void update(sf::RenderWindow& window, I_UI<sf::VertexArray>* tabuleiroUI)
{
    window.clear();
    tabuleiroUI->draw(&window);
    window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "XADREZ", sf::Style::Titlebar | sf::Style::Close);
	int tamanho_casas = 100;
	Tabuleiro tabuleiro(tamanho_casas, true);
	I_UI<sf::VertexArray>* tabuleiroUI = &tabuleiro;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				int pos_x = (int)( sf::Mouse::getPosition(window).x/tamanho_casas), pos_y = (int)(sf::Mouse::getPosition(window).y/tamanho_casas);

				while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					tabuleiro.newPosObject(pos_x, pos_y, {(float) sf::Mouse::getPosition(window).x, (float) sf::Mouse::getPosition(window).y}, sf::Mouse::isButtonPressed(sf::Mouse::Left));
					update(window, tabuleiroUI);
				}
				tabuleiro.newPosObject(pos_x, pos_y, {(float) sf::Mouse::getPosition(window).x, (float) sf::Mouse::getPosition(window).y}, sf::Mouse::isButtonPressed(sf::Mouse::Left));
			}
		}
		update(window, tabuleiroUI);
	}
	return 0;
}