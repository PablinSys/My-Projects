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
bool Peça::addNewPos(int x, int y, bool isMoviment)
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


#include <memory>
#include <string>
#include <stdexcept>

std::unique_ptr<Peça> PeçasInstances::criarPeça(const std::string& tipo, const std::filesystem::path& caminho, const sf::Vector2f& pos, Tabuleiro& tabuleiro, bool isWhite) {
        if (tipo == "peao") {
            return std::make_unique<Peao>(caminho, pos, tabuleiro, isWhite);
        }
        else if (tipo == "torre") {
            return std::make_unique<Torre>(caminho, pos, tabuleiro, isWhite);
        }
        else if (tipo == "bispo") {
            return std::make_unique<Bispo>(caminho, pos, tabuleiro, isWhite);
        }
        else if (tipo == "cavalo") {
            return std::make_unique<Cavalo>(caminho, pos, tabuleiro, isWhite);
        }
        else if (tipo == "rainha") {
            return std::make_unique<Rainha>(caminho, pos, tabuleiro, isWhite);
        }
        else if (tipo == "rei") {
            return std::make_unique<Rei>(caminho, pos, tabuleiro, isWhite);
        }
        throw std::invalid_argument("Tipo de peça desconhecido");
}

