#include "../include/peças.hpp"

Peça::Peça(const std::string& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
{
    tab = &tabuleiro; this->isBranco = isBranco; this->position = position; objectUI = new sf::Sprite;
    if (!peça_img.loadFromFile(path_img, sf::IntRect({(int)position.x, (int)position.y}, {32, 32})))
        throw std::runtime_error("Erro ao carregar a textura");
    objectUI->setTexture(peça_img);
}
bool Peça::addNewPos(int x, int y)
{
    position.x = x; position.y = y;
    objectUI->setPosition(position); // Atualiza a posição da peça *temporário por enquanto até implementar animação
    return true;
}
Peça::~Peça()
{
    delete objectUI;
}

/* SEM IMPLEMENTAÇÃO AINDA */

bool Peao::analisarMovimento(const sf::Vector2f& pos) { return true; } 
bool Torre::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Bispo::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Cavalo::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Rainha::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Rei::analisarMovimento(const sf::Vector2f& pos) { return true; }