#include <filesystem>
#include "../include/peças.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

/*
POSIÇÕES DAS PEÇAS NO TABULEIRO *APROXIMADO : 
    - POR MATRIX :
        0 - 0 1 2 3 4 5 6 7 <-- LOCAL DAS PEÇAS DO OPONENTE
        1 - 0 1 2 3 4 5 6 7 <-- LOCAL DAS PEÇAS DO OPONENTE
        2 - 0 1 2 3 4 5 6 7 <-- INICIALMENTE VAZIO
        3 - 0 1 2 3 4 5 6 7 <-- INICIALMENTE VAZIO
        4 - 0 1 2 3 4 5 6 7 <-- INICIALMENTE VAZIO
        5 - 0 1 2 3 4 5 6 7 <-- INICIALMENTE VAZIO
        6 - 0 1 2 3 4 5 6 7 <-- LOCAL DAS PEÇAS DO JOGADO PRINCIPAL
        7 - 0 1 2 3 4 5 6 7 <-- LOCAL DAS PEÇAS DO JOGADO PRINCIPAL

    - PELO WINDOW, PARTIDA INICIAL : 
        0 -> 0 100 200 300 400 500 600 700 800 <-- LOCAL DAS PEÇAS DO OPONENTE
      100 -> 0 100 200 300 400 500 600 700 800 <-- LOCAL DAS PEÇAS DO OPONENTE
      200 -> 0 100 200 300 400 500 600 700 800 <-- INICIALMENTE VAZIO
      300 -> 0 100 200 300 400 500 600 700 800 <-- INICIALMENTE VAZIO
      400 -> 0 100 200 300 400 500 600 700 800 <-- INICIALMENTE VAZIO
      500 -> 0 100 200 300 400 500 600 700 800 <-- INICIALMENTE VAZIO
      600 -> 0 100 200 300 400 500 600 700 800 <-- LOCAL DAS PEÇAS DO JOGADO PRINCIPAL
  700-800 -> 0 100 200 300 400 500 600 700 800 <-- LOCAL DAS PEÇAS DO JOGADO PRINCIPAL
*/

Peça::Peça(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco)
{
    tab = &tabuleiro; this->isBranco = isBranco; objectUI = new sf::Sprite;
    if (!peça_img.loadFromFile(path_img))
        throw std::runtime_error("Erro ao carregar a textura");
    
    positionIndex = indexPosition; //{tabuleiro.getPositionX(position.x), tabuleiro.getPositionY(position.y)};
    
    peça_img.setSmooth(true);
    objectUI->setScale(2, 2);
    objectUI->setTexture(peça_img);
    objectUI->setPosition({position.x, position.y});
}
bool Peça::addNewPos(int x, int y, bool isMoviment)
{
    if (isMoviment)
    {
        objectUI->setPosition(x, y);
    }
    else if (analisarMovimento({x, y}))
    {
        objectUI->setPosition(x, y);
        return true;
    }
    return false;
}
Peça::~Peça()
{
    delete objectUI;
}

Peao::Peao(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco, const bool& primeiroLance)
    : Peça(path_img, position, indexPosition, tabuleiro, isBranco) , primeiroLance(primeiroLance) {}
Torre::Torre(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, indexPosition, tabuleiro, isBranco) {}
Bispo::Bispo(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, indexPosition, tabuleiro, isBranco) {}
Cavalo::Cavalo(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, indexPosition, tabuleiro, isBranco) {}
Rainha::Rainha(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, indexPosition, tabuleiro, isBranco), Bispo(path_img, position, indexPosition, tabuleiro, isBranco), Torre(path_img, position, indexPosition, tabuleiro, isBranco) {}
Rei::Rei(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, indexPosition, tabuleiro, isBranco) {}

bool Peao::analisarMovimento(const sf::Vector2i& new_pos) 
{ 
    int index_x = positionIndex.x, index_y = positionIndex.y;
    int new_index_x = (int)(new_pos.x / tab->tamanho_casas); int new_index_y = (int)(new_pos.y / tab->tamanho_casas);

    if (new_index_x >= 0 && new_index_y >= 0)
    {
        // Primeira regra : o peão não pode andar mais de uma casa se for o primeiro lance
        if (primeiroLance && new_index_x == index_x && (index_y - 2 == new_index_y && index_y - 2 >= 0) && tab->getTabuleiro()[new_index_y][new_index_x] == nullptr){}
        // Segunda regra : caso andar 1 casa a frente, tenha nenhuma peça a frente
        else if (index_x == new_index_x && (index_y - 1 == new_index_y && index_y - 1 >= 0) && tab->getTabuleiro()[new_index_y][new_index_x] == nullptr){}
        // Quarta regra : o peão pode comer peças nas diagonais caso tiver um
        else if((index_x - 1 == new_index_x || index_x + 1 == new_index_x) && 
                (index_x+1 < 8 && index_x-1 >= 0) && 
                (index_y - 1 == new_index_y && index_y - 1 >= 0) && 
                tab->getTabuleiro()[new_index_y][new_index_x] != nullptr)
        {
            if (tab->getTabuleiro()[new_index_y][new_index_x]->isBranco == isBranco)
                return false;
        }
        else 
            return false;
    }
    else 
        return false;
    return true; 
}
bool Torre::analisarMovimento(const sf::Vector2i& new_pos) 
{ 
    int index_x = positionIndex.x, index_y = positionIndex.y;
    int new_index_x = (int)(new_pos.x / tab->tamanho_casas); int new_index_y = (int)(new_pos.y / tab->tamanho_casas);

    if (tab->getTabuleiro()[new_index_y][new_index_x] != nullptr)
        if (tab->getTabuleiro()[new_index_y][new_index_x]->isBranco == isBranco)
            return false;
    // Primeira regra : enquanto tiver casas na frente disponíveis sem nenhuma peça amiga ou inimiga, pode andar em qualquer uma -> HORIZONTAL
    //  CIMA :
    if (index_x == new_index_x && index_y != new_index_y)
    {
        if (index_y > new_index_y)
            for (int i = 1; i < index_y; i++) // index_y - i 
            {
                if (index_y - i == new_index_y)
                    break;
                else if (tab->getTabuleiro()[index_y - i][index_x] != nullptr)
                    return false;
            }
        //  BAIXO : 
        if (index_y < new_index_y)
            for (int i = 1; i < 8 - index_y; i++) // 8 - index_y - i
            {
                if (index_y + i == new_index_y)
                    break;
                else if (tab->getTabuleiro()[index_y + i][index_x] != nullptr)
                    return false;
            }
    }
    // Segunda Regra : enquanto tiver casas nas laterais disponíveis sem nenhuma peça amiga ou inimiga, pode andar em qualquer uma -> VERTICAL
    //  ESQUERDA :
    else if (index_y == new_index_y && index_x != new_index_x)
    {
        if (index_x > new_index_x)
            for (int i = 1; i < index_x; i++) // index_x - i
            {
                if (index_x - i == new_index_x)
                    break;
                else if (tab->getTabuleiro()[index_y][index_x - i] != nullptr)
                    return false;
            }
        //  DIREITA : 
        if (index_x < new_index_x)
            for (int i = 1; i < 8 - index_x; i++) // 8 - index_x + i
            {
                if (index_x + i == new_index_x)
                    break;
                else if (tab->getTabuleiro()[index_y][index_x + i] != nullptr)
                    return false;
            }
    }
    else 
        return false;
    return true;
}
bool Bispo::analisarMovimento(const sf::Vector2i& new_pos) 
{
    int index_x = positionIndex.x, index_y = positionIndex.y;
    int new_index_x = (int)(new_pos.x / tab->tamanho_casas); int new_index_y = (int)(new_pos.y / tab->tamanho_casas);
    
    if (std::abs(index_x - new_index_x) != std::abs(index_y - new_index_y))
        return false;
    else if (tab->getTabuleiro()[new_index_y][new_index_x] != nullptr)
        if (tab->getTabuleiro()[new_index_y][new_index_x]->isBranco == isBranco)
            return false;

    // Primeira regra : enquanto tiver casas na diagonal disponiveis sem nenhuma peça, pode andar em qualquer uma
    if (index_y > new_index_y && index_x != new_index_x && index_y)
    {
        //  SUPERIOR ESQUERDO :
        if (index_x > new_index_x)
        {
            for (int i = 1; i < index_y; i++)
            {
                if (index_y - i == new_index_y && index_x - i == new_index_x && index_x - i >= 0)
                    break;
                else if (tab->getTabuleiro()[index_y - i][index_x - i] != nullptr)
                    return false;
            }
        }
        //  SUPERIOR DIREITO :
        else if (index_x < new_index_x)
        {
            for (int i = 1; i < index_y; i++)
            {
                if (index_y - i == new_index_y && index_x + i == new_index_x && index_x + i < 8)
                    break;
                else if (tab->getTabuleiro()[index_y - i][index_x + i] != nullptr)
                    return false;
            }
        }
    }
    //  INFERIOR ESQUERDO :
    else if (index_y < new_index_y && index_x != new_index_x)
    {
        if (index_x > new_index_x)
        {
            for (int i = 1; i < 8 - index_y; i++)
            {
                if (index_y + i == new_index_y && index_x - i == new_index_x && index_x - i >= 0)
                    break;
                else if (tab->getTabuleiro()[index_y + i][index_x - i] != nullptr)
                    return false;
            }
        }
        else if (index_x > new_index_x)
        {
            for (int i = 1; i < 8 - index_y; i++)
            {
                if (index_y + i == new_index_y && index_x + i == new_index_x && index_x + i < 8)
                    break;
                else if (tab->getTabuleiro()[index_y + i][index_x + i] != nullptr)
                    return false;
            }
        }
    }
    else 
        return false;
    return true; 
}
bool Cavalo::analisarMovimento(const sf::Vector2i& new_pos)  
{ 
    int index_x = positionIndex.x, index_y = positionIndex.y;
    int new_index_x = (int)(new_pos.x / tab->tamanho_casas); int new_index_y = (int)(new_pos.y / tab->tamanho_casas);
    
    if (tab->getTabuleiro()[new_index_y][new_index_x] != nullptr)
                if (tab->getTabuleiro()[new_index_y][new_index_x]->isBranco == isBranco)
                    return false;
    // Primeira regra : pode se posicionar dentre os 8 movimentos possiveis entre os limites da tabela e sem posicionar nenhuma posição de peça amiga 
    //  HORIZONTAL :
    //      CIMA :
    if ((std::abs(index_y - new_index_y) == 2 && std::abs(index_x - new_index_x) == 1) || 
        (std::abs(index_x - new_index_x) == 2 && std::abs(index_y - new_index_y) == 1))
    {
        if (index_y - 2 == new_index_y && index_y - 2 >= 0)
        {
            if ((index_x - 1 == new_index_x && index_x - 1 >= 0) || (index_x + 1 == new_index_x && index_x + 1 < 8))
                return true;
            else 
                return false;
        }
        //      BAIXO :
        else if (index_y + 2 == new_index_y && index_y + 2 < 8)
        {
            if ((index_x - 1 == new_index_x && index_x - 1 >= 0) || (index_x + 1 == new_index_x && index_x + 1 < 8))
                return true;
            else 
                return false;
        }
        //  VERTICAL :
        //      ESQUERDA :
        else if (index_x - 2 == new_index_x && index_x - 2 >= 0)
        {
            if ((index_y - 1 == new_index_y && index_y - 1 >= 0) || (index_y + 1 == new_index_y && index_y + 1 < 8))
                return true;
            else 
                return false;
        }
        //      DIREITA :
        else if (index_x + 2 == new_index_x && index_x + 2 < 8)
        {
            if ((index_y - 1 == new_index_y && index_y - 1 >= 0) || (index_y + 1 == new_index_y && index_y + 1 < 8))
                return true;
            else 
                return false;
            
        }
    }
    return false; 
}
bool Rainha::analisarMovimento(const sf::Vector2i& new_pos)
{
    // Analisando movimentos diagonais, horizontais e verticais da Peça
    return Torre::analisarMovimento(new_pos) || Bispo::analisarMovimento(new_pos);
}
bool Rei::analisarMovimento(const sf::Vector2i& new_pos) 
{ 
    int index_x = positionIndex.x, index_y = positionIndex.y;
    int new_index_x = (int)(new_pos.x / tab->tamanho_casas); int new_index_y = (int)(new_pos.y / tab->tamanho_casas);

    if (tab->getTabuleiro()[new_index_y][new_index_x] != nullptr)
        if (tab->getTabuleiro()[new_index_y][new_index_x]->isBranco == isBranco)
            return false;

    // Primeira regra : pode se posicionar entre as casas ao redor do rei e sem posicionar nenhuma peça amiga
    int init_x = index_x-1, init_y = index_y-1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (init_x + j == index_x && init_y + i == index_y)
                continue;
            else if (init_x + j == new_index_x && init_y + i == new_index_y && 
                     init_x + j < 8 && init_y + i < 8)
                return true;
        }
    return false; 
}

std::unique_ptr<Peça> PeçasInstances::criarPeça(const std::type_info& tipo, const std::filesystem::path& caminho, const sf::Vector2f& pos, const sf::Vector2i& indexpos, Tabuleiro& tabuleiro, bool isWhite) {
    if (tipo == typeid(Peao)) {
        return std::make_unique<Peao>(caminho, pos, indexpos, tabuleiro, isWhite);
    }
    else if (tipo == typeid(Torre)) {
        return std::make_unique<Torre>(caminho, pos, indexpos, tabuleiro, isWhite);
    }
    else if (tipo == typeid(Bispo)) {
        return std::make_unique<Bispo>(caminho, pos, indexpos, tabuleiro, isWhite);
    }
    else if (tipo == typeid(Cavalo)) {
        return std::make_unique<Cavalo>(caminho, pos, indexpos, tabuleiro, isWhite);
    }
    else if (tipo == typeid(Rainha)) {
        return std::make_unique<Rainha>(caminho, pos, indexpos, tabuleiro, isWhite);
    }
    else if (tipo == typeid(Rei)) {
        return std::make_unique<Rei>(caminho, pos, indexpos, tabuleiro, isWhite);
    }
    throw std::invalid_argument("Tipo de peça desconhecido");
}

