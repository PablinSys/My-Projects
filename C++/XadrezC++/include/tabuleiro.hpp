#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "../include/I_UI.hpp"
class Tabuleiro : public I_UI<sf::VertexArray>
{
	public :
		Tabuleiro(const int& tamanho);
        bool addNewPos(int x, int y) override;
        ~Tabuleiro();
};
#endif
