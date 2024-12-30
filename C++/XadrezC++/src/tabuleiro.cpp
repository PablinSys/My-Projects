#include "../include/tabuleiro.hpp"

Tabuleiro::Tabuleiro(const int& tamanho)
{
    int qtdVertices = 4*8*8, pos_x = 0, pos_y = 0, index = 0;
    objectUI = sf::VertexArray(sf::Quads, qtdVertices);
    bool casasPretas = true;
    for(int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++){
            pos_x = x*tamanho; pos_y = y*tamanho;
            objectUI[index].position = sf::Vector2f(pos_x, pos_y);
            if (casasPretas) objectUI[index].color = sf::Color::Black;
            else objectUI[index].color = sf::Color::White;
            objectUI[++index].position = sf::Vector2f(pos_x+tamanho, pos_y);
            if (casasPretas) objectUI[index].color = sf::Color::Black;
            else objectUI[index].color = sf::Color::White;
            objectUI[++index].position = sf::Vector2f(pos_x, pos_y+tamanho);
            if (casasPretas) objectUI[index].color = sf::Color::Black;
            else objectUI[index].color = sf::Color::White;
            objectUI[++index].position = sf::Vector2f(pos_x+tamanho, pos_y+tamanho);
            if (casasPretas) objectUI[index].color = sf::Color::Black;
            else objectUI[index].color = sf::Color::White;

            casasPretas = !casasPretas;
        }
}
bool Tabuleiro::addNewPos(int x, int y){return true;}
Tabuleiro::~Tabuleiro() = default;