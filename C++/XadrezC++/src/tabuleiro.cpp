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
    peças_brancas = new Peça*[16]; peças_pretas = new Peça*[16];
    float pos_peça_x = tamanho/2 - 60, pos_peça_y = tamanho*7 - tamanho/2 - 60;
    // ADICIONANDO PEÇAS BRANCAS 
    for (int i = 0; i < 16; i++)
    {
        if (brancasPrimeiro)
        {
            if (i < 8) peças_brancas[i] = new Peao(std::filesystem::current_path() / "assets/white/peao.png", sf::Vector2f(pos_peça_x+i*tamanho, pos_peça_y), *this, true);
            else if (i == 8 || i == 15) peças_brancas[i] = new Torre(std::filesystem::current_path() / "assets/white/torre.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, true);
            else if (i == 9 || i == 14) peças_brancas[i] = new Cavalo(std::filesystem::current_path() / "assets/white/cavalo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, true);
            else if (i == 10 || i == 13) peças_brancas[i] = new Bispo(std::filesystem::current_path() / "assets/white/bispo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, true);
            else if (i == 11) peças_brancas[i] = new Rei(std::filesystem::current_path() / "assets/white/rei.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, true);
            else if (i == 12) peças_brancas[i] = new Rainha(std::filesystem::current_path() / "assets/white/rainha.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, true);
        }
        else
        {
            if (i < 8) peças_pretas[i] = new Peao( std::filesystem::current_path() / "assets/black/peao.png", sf::Vector2f(pos_peça_x+i*tamanho, pos_peça_y), *this, false);
            else if (i == 8 || i == 15) peças_pretas[i] = new Torre(std::filesystem::current_path() / "assets/black/torre.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, false);
            else if (i == 9 || i == 14) peças_pretas[i] = new Cavalo(std::filesystem::current_path() / "assets/black/cavalo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, false);
            else if (i == 10 || i == 13) peças_pretas[i] = new Bispo(std::filesystem::current_path() / "assets/black/bispo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, false);
            else if (i == 11) peças_pretas[i] = new Rei(std::filesystem::current_path() / "assets/black/rei.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, false);
            else if (i == 12) peças_pretas[i] = new Rainha(std::filesystem::current_path() / "assets/black/rainha.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y+tamanho), *this, false);

        }
    }
    pos_peça_y = tamanho*2 - tamanho/2 - 60;
    for (int i = 0; i < 16; i++)
    {
        if (brancasPrimeiro)
        {
            if (i < 8) peças_pretas[i] = new Peao(std::filesystem::current_path() / "assets/black/peao.png", sf::Vector2f(pos_peça_x+i*tamanho, pos_peça_y), *this, false);
            else if (i == 8 || i == 15) peças_pretas[i] = new Torre(std::filesystem::current_path() / "assets/black/torre.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, false);
            else if (i == 9 || i == 14) peças_pretas[i] = new Cavalo(std::filesystem::current_path() / "assets/black/cavalo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, false);
            else if (i == 10 || i == 13) peças_pretas[i] = new Bispo(std::filesystem::current_path() / "assets/black/bispo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, false);
            else if (i == 11) peças_pretas[i] = new Rei(std::filesystem::current_path() / "assets/black/rei.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, false);
            else if (i == 12) peças_pretas[i] = new Rainha(std::filesystem::current_path() / "assets/black/rainha.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, false);
        }
        else
        {
            if (i < 8) peças_brancas[i] = new Peao(std::filesystem::current_path() / "assets/white/peao.png", sf::Vector2f(pos_peça_x+i*tamanho, pos_peça_y), *this, true);
            else if (i == 8 || i == 15) peças_brancas[i] = new Torre(std::filesystem::current_path() / "assets/white/torre.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, true);
            else if (i == 9 || i == 14) peças_brancas[i] = new Cavalo(std::filesystem::current_path() / "assets/white/cavalo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, true);
            else if (i == 10 || i == 13) peças_brancas[i] = new Bispo(std::filesystem::current_path() / "assets/white/bispo.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, true);
            else if (i == 11) peças_brancas[i] = new Rei(std::filesystem::current_path() / "assets/white/rei.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, true);
            else if (i == 12) peças_brancas[i] = new Rainha(std::filesystem::current_path() / "assets/white/rainha.png", sf::Vector2f(pos_peça_x+(i-8)*tamanho, pos_peça_y-tamanho), *this, true);
        }
    }
}
void Tabuleiro::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < 64; i++)
    {
        window->draw(objectUI[i]);
    }
    for (int i = 0; i < 16; i++)
    {
        peças_brancas[i]->draw(window);
        peças_pretas[i]->draw(window);
    }
}
bool Tabuleiro::addNewPos(int x, int y){return true;}
Tabuleiro::~Tabuleiro()
{
    delete[] objectUI;
}