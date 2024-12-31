#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "../include/I_UI.hpp"
#include "../include/peças.hpp"

class Peça;
class Tabuleiro : public I_UI<sf::VertexArray>
{
    private :
        Peça*** tabuleiro;
        const int tamanho_casas;
        const bool começouBrancas;
	public :
		Tabuleiro(const int& tamanho, const bool& brancasPrimeiro);
        bool addNewPos(int x, int y, bool isMoviment) override;
        void newPosObject(int index_x, int index_y, sf::Vector2f new_pos, bool isMoviment);
        void draw(sf::RenderWindow* window) override;
        ~Tabuleiro();
};
#endif
