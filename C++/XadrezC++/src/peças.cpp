#include <filesystem>
#include "../include/peças.hpp"
#include <iostream>

Peça::Peça(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
{
    tab = &tabuleiro; this->isBranco = isBranco; this->position = position; objectUI = new sf::Sprite;
    if (!peça_img.loadFromFile(path_img))
        throw std::runtime_error("Erro ao carregar a textura");
    
    peça_img.setSmooth(true);
    objectUI->setScale(2, 2);
    objectUI->setTexture(peça_img);
    objectUI->setPosition({position.x, position.y});
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

Peao::Peao(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, tabuleiro, isBranco) {}
Torre::Torre(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, tabuleiro, isBranco) {}
Bispo::Bispo(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, tabuleiro, isBranco) {}
Cavalo::Cavalo(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, tabuleiro, isBranco) {}
Rainha::Rainha(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, tabuleiro, isBranco) {}
Rei::Rei(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco)
    : Peça(path_img, position, tabuleiro, isBranco) {}

/* AINDA NÃO IMPLEMENTADO */
bool Peao::analisarMovimento(const sf::Vector2f& pos) { return true; } 
bool Torre::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Bispo::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Cavalo::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Rainha::analisarMovimento(const sf::Vector2f& pos) { return true; }
bool Rei::analisarMovimento(const sf::Vector2f& pos) { return true; }