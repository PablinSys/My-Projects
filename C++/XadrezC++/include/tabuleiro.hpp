#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "../include/I_UI.hpp"
#include "../include/peças.hpp"

class Peça;
class Tabuleiro : public I_UI<sf::VertexArray>
{
    private :
        Peça** tabuleiro;
	public :
		Tabuleiro(const int& tamanho, const bool& brancasPrimeiro);
        bool addNewPos(int x, int y) override;
        void draw(sf::RenderWindow* window) override;
        ~Tabuleiro();
};
#endif
