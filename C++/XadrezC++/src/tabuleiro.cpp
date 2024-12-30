#include "../include/tabuleiro.hpp"

Tabuleiro::Tabuleiro(const int& tamanho, const bool& brancasPrimeiro)
{
    int qtdVertices = 4, pos_x = 0, pos_y = 0, index = 0;
    objectUI = new sf::VertexArray[64];

//  CRIANDO O TABULEIRO DE 8x8
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
                    objectUI[index][i].color = sf::Color(111, 149, 81); // Cor das casas pretas *Chess.com
                else
                    objectUI[index][i].color = sf::Color::White;
            }

            casasPretas = !casasPretas;
            index++;
        }
        casasPretas = !casasPretas;
    }

//  ADICIONANDO AS PEÇAS NO TABULEIRO
    tabuleiro = new Peça*[64];
    float pos_peça_x = tamanho/2 - 60, pos_peça_y = tamanho*7 - tamanho/2 - 60;
    // ADICIONANDO AS 2 COLUNAS COM PEÇAS MAIS A BAIXO DO TABULEIRO
    for (int i = 0; i < 16; i++)
    {
        bool isWhite = brancasPrimeiro;
        std::string color = isWhite ? "white" : "black";

        if (i < 8)
            tabuleiro[i] = new Peao(std::filesystem::current_path() / ("assets/" + color + "/peao.png"), sf::Vector2f(pos_peça_x + i * tamanho, pos_peça_y), *this, isWhite);
        else if (i == 8 || i == 15)
            tabuleiro[i] = new Torre(std::filesystem::current_path() / ("assets/" + color + "/torre.png"), sf::Vector2f(pos_peça_x + (i - 8) * tamanho, pos_peça_y + tamanho), *this, isWhite);
        else if (i == 9 || i == 14)
            tabuleiro[i] = new Cavalo(std::filesystem::current_path() / ("assets/" + color + "/cavalo.png"), sf::Vector2f(pos_peça_x + (i - 8) * tamanho, pos_peça_y + tamanho), *this, isWhite);
        else if (i == 10 || i == 13)
            tabuleiro[i] = new Bispo(std::filesystem::current_path() / ("assets/" + color + "/bispo.png"), sf::Vector2f(pos_peça_x + (i - 8) * tamanho, pos_peça_y + tamanho), *this, isWhite);
        else if (i == 11)
            tabuleiro[i] = new Rei(std::filesystem::current_path() / ("assets/" + color + "/rei.png"), sf::Vector2f(pos_peça_x + (i - 8) * tamanho, pos_peça_y + tamanho), *this, isWhite);
        else if (i == 12)
            tabuleiro[i] = new Rainha(std::filesystem::current_path() / ("assets/" + color + "/rainha.png"), sf::Vector2f(pos_peça_x + (i - 8) * tamanho, pos_peça_y + tamanho), *this, isWhite);
    }
    pos_peça_y = tamanho*2 - tamanho/2 - 60;
    int pulo = 64 - 16;
    // ADICIONANDO 2 COLUNAS DE PEÇAS MAIS A CIMA DO TABULEIRO
    for (int i = pulo; i < 64; i++)
    {
        bool isWhite = !brancasPrimeiro;
        std::string color = isWhite ? "white" : "black";

        if (i < pulo + 8)
            tabuleiro[i] = new Peao(std::filesystem::current_path() / ("assets/" + color + "/peao.png"), sf::Vector2f(pos_peça_x + (i - pulo) * tamanho, pos_peça_y), *this, isWhite);
        else if (i == pulo + 8 || i == pulo + 15)
            tabuleiro[i] = new Torre(std::filesystem::current_path() / ("assets/" + color + "/torre.png"), sf::Vector2f(pos_peça_x + (i - pulo - 8) * tamanho, pos_peça_y - tamanho), *this, isWhite);
        else if (i == pulo + 9 || i == pulo + 14)
            tabuleiro[i] = new Cavalo(std::filesystem::current_path() / ("assets/" + color + "/cavalo.png"), sf::Vector2f(pos_peça_x + (i - pulo - 8) * tamanho, pos_peça_y - tamanho), *this, isWhite);
        else if (i == pulo + 10 || i == pulo + 13)
            tabuleiro[i] = new Bispo(std::filesystem::current_path() / ("assets/" + color + "/bispo.png"), sf::Vector2f(pos_peça_x + (i - pulo - 8) * tamanho, pos_peça_y - tamanho), *this, isWhite);
        else if (i == pulo + 11)
            tabuleiro[i] = new Rei(std::filesystem::current_path() / ("assets/" + color + "/rei.png"), sf::Vector2f(pos_peça_x + (i - pulo - 8) * tamanho, pos_peça_y - tamanho), *this, isWhite);
        else if (i == pulo + 12)
            tabuleiro[i] = new Rainha(std::filesystem::current_path() / ("assets/" + color + "/rainha.png"), sf::Vector2f(pos_peça_x + (i - pulo - 8) * tamanho, pos_peça_y - tamanho), *this, isWhite);
    }
}
void Tabuleiro::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < 64; i++)
    {
        window->draw(objectUI[i]);
    }
    for (int i = 0; i < 64; i++)
    {
        if (i < 16 || i >= 48)
            tabuleiro[i]->draw(window);
    }
}
bool Tabuleiro::addNewPos(int x, int y){return true;}
Tabuleiro::~Tabuleiro()
{
    delete[] objectUI;
}