#include <SFML/Graphics.hpp>
#include "../include/tabuleiro.hpp"
#include "../include/I_UI.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "XADREZ", sf::Style::Titlebar | sf::Style::Close);
	int tamanho_casas = 100;
	Tabuleiro tabuleiro(tamanho_casas, true);
	I_UI<sf::VertexArray>* tabuleiroUI = &tabuleiro;

	bool mouseIsPressed = false;
	bool mouseIsReleased = false;

	int* pos_x_anterior; int* pos_y_anterior;

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
				mouseIsPressed = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				mouseIsReleased = true;
			}
		}
		if (mouseIsPressed)
		{
			int pos_x = (int)(event.mouseButton.x/tamanho_casas), pos_y = (int)(event.mouseButton.y/tamanho_casas);
			if (pos_x_anterior == nullptr || pos_y_anterior == nullptr) 
			{
				pos_x_anterior = new int(pos_x);
				pos_y_anterior = new int(pos_y);
			}
			tabuleiro.newPosObject(*pos_x_anterior, *pos_y_anterior, {(float)event.mouseButton.x, (float)event.mouseButton.y}, true);
		}
		if (mouseIsReleased)
		{
			tabuleiro.newPosObject(*pos_x_anterior, *pos_y_anterior, {(float)event.mouseButton.x, (float)event.mouseButton.y}, false);
			pos_x_anterior = nullptr; pos_y_anterior = nullptr;
			mouseIsPressed = false; mouseIsReleased = false;
		}
		tabuleiroUI->draw(&window);
		window.display();
		sf::sleep(sf::seconds(1));
	}
	return 0;
}