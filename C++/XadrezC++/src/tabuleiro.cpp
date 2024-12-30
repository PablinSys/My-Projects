#include "../include/tabuleiro.hpp"

Tabuleiro::Tabuleiro(const int& tamanho)
{
    int qtdVertices = 4, pos_x = 0, pos_y = 0, index = 0;
    objectUI = new sf::VertexArray[64];

    bool casasPretas = true;
    for(int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++){
            pos_x = x*tamanho; pos_y = y*tamanho;
            objectUI[index].setPrimitiveType(sf::PrimitiveType::Quads); objectUI[index].resize(qtdVertices);

            for (int i = 0; i < qtdVertices; i++)
            {
                int distance_x = i == 1 || i == 2 ? tamanho : 0, distance_y = i == 3 || i == 2 ? tamanho : 0;

                objectUI[index][i].position = sf::Vector2f(pos_x + distance_x, pos_y + distance_y);
                if (casasPretas)
                    objectUI[index][i].color = sf::Color::Black;
                else
                    objectUI[index][i].color = sf::Color::White;
                
            }

            casasPretas = !casasPretas;
            index++;
        }
        casasPretas = !casasPretas;
    }
}
void Tabuleiro::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < 64; i++)
    {
        window->draw(objectUI[i]);
    }
}
bool Tabuleiro::addNewPos(int x, int y){return true;}
Tabuleiro::~Tabuleiro()
{
    delete[] objectUI;
}