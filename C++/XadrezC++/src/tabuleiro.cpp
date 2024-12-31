#include "../include/tabuleiro.hpp"
#include <iostream>

Tabuleiro::Tabuleiro(const int& tamanho, const bool& brancasPrimeiro)
    : tamanho_casas(tamanho), começouBrancas(brancasPrimeiro)
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
// INICIANDO O TABULEIRO
    tabuleiro = new Peça**[8];
    for (int i = 0; i < 8; i++)
    {
        tabuleiro[i] = new Peça*[8];
    }
//  ADICIONANDO AS PEÇAS NO TABULEIRO :
    // ADICIONANDO AS 2 COLUNAS COM PEÇAS MAIS A BAIXO DO TABULEIRO
    int index_real_y = 0;
    for (int index_y = 0; index_y < 8; index_y++)
    {
        if (index_y < 2)
        {
            index_real_y = 7 - index_y;
            for (int index_x = 0; index_x < 8; index_x++)
            {
                bool isWhite = brancasPrimeiro;
                std::string color = isWhite ? "white" : "black";
                int pos_x = tamanho/2 + tamanho*index_x - 60, pos_y = (8 - index_y)*tamanho - tamanho/2 - 60;
                std::string tipo;
                switch (index_x)
                {
                    case 0:
                    case 7:
                        tipo = "torre";
                        break;
                    case 1:
                    case 6:
                        tipo = "cavalo";
                        break;
                    case 2:
                    case 5:
                        tipo = "bispo";
                        break;
                    case 3:
                        tipo = "rei";
                        break;
                    case 4:
                        tipo = "rainha";
                        break;
                }
                if (index_y == 1) tipo = "peao";
                tabuleiro[index_real_y][index_x] = PeçasInstances::criarPeça(tipo, std::filesystem::current_path() / ("assets/" + color + "/" + tipo + ".png"), sf::Vector2f(pos_x, pos_y), *this, isWhite).release();
            }
        }
        else if (index_y > 5)
        {
            index_real_y = std::abs(7 - index_y);
            for (int index_x = 0; index_x < 8; index_x++)
            {
                bool isWhite = !brancasPrimeiro;
                std::string color = isWhite ? "white" : "black";
                int pos_x = tamanho/2 + tamanho*index_x - 60, pos_y = (8 - index_y)*tamanho - tamanho/2 - 60;
                std::string tipo;
                switch (index_x)
                {
                    case 0:
                    case 7:
                        tipo = "torre";
                        break;
                    case 1:
                    case 6:
                        tipo = "cavalo";
                        break;
                    case 2:
                    case 5:
                        tipo = "bispo";
                        break;
                    case 3:
                        tipo = "rei";
                        break;
                    case 4:
                        tipo = "rainha";
                        break;
                }
                if (index_y == 6) tipo = "peao";
                tabuleiro[index_real_y][index_x] = PeçasInstances::criarPeça(tipo, std::filesystem::current_path() / ("assets/" + color + "/" + tipo + ".png"), sf::Vector2f(pos_x, pos_y), *this, isWhite).release();
            }
        }
    }
}
void Tabuleiro::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < 64; i++)
    {
        window->draw(objectUI[i]);
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (i < 2 || i > 5) 
                tabuleiro[i][j]->draw(window);
        
}
bool Tabuleiro::addNewPos(int x, int y, bool isMoviment){return false;}
void Tabuleiro::newPosObject(int index_x, int index_y, sf::Vector2f new_pos, bool isMoviment)
{
    if (tabuleiro[index_y][index_x] != nullptr) {
        std::cout << "Movendo peça para (" << index_x << ", " << index_y << ") to position (" << new_pos.x << ", " << new_pos.y << ")" << std::endl;
        
        if (!isMoviment && tabuleiro[index_y][index_x]->addNewPos(new_pos.x, new_pos.y, isMoviment)) {
            int new_index_x = static_cast<int>(new_pos.x / tamanho_casas);
            int new_index_y = static_cast<int>(new_pos.y / tamanho_casas);
            bool isWhite = começouBrancas;

            std::string tipo = typeid(*tabuleiro[index_y][index_x]).name(); // Obtém o tipo da peça
            std::transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);
            std::cout << "Peça type: " << tipo << std::endl;
            
            std::unique_ptr<Peça> novaPeça = PeçasInstances::criarPeça(tipo, std::filesystem::current_path() / ("assets/" + std::string(isWhite ? "white" : "black") + "/" + tipo + ".png"), new_pos, *this, isWhite);
            tabuleiro[new_index_y][new_index_x] = novaPeça.release();
            tabuleiro[index_y][index_x] = nullptr;

            std::cout << "Peça movida : (" << new_index_x << ", " << new_index_y << ")" << std::endl;

            tabuleiro[new_index_y][new_index_x]->addNewPos(new_index_x * tamanho_casas / 2 - 60, new_index_y * tamanho_casas - tamanho_casas / 2 - 60, !isMoviment);
        }
    }
    else {
        std::cout << "Não a peças (" << index_x << ", " << index_y << ") to move." << std::endl;
    }
}

Tabuleiro::~Tabuleiro()
{
    for (int i = 0; i < 8; i++)
    {
        delete[] tabuleiro;
    }
    delete tabuleiro;
    delete objectUI;
}