#ifndef PEÇAS_H
#define PEÇAS_H

#include <filesystem>
#include "I_UI.hpp"
#include "tabuleiro.hpp"

class Tabuleiro;
class Peça : public I_UI<sf::Sprite> //classe abstrata
{
	protected :
		sf::Texture peça_img;
		Tabuleiro* tab;
		bool isBranco;
		virtual bool analisarMovimento(const sf::Vector2f& pos) = 0;
	public : 
		Peça(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
		bool addNewPos(int x, int y, bool isMoviment) override;
		~Peça();
};
class Peao : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) override;
	public :
		Peao(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Torre : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) override;
	public :
		Torre(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Cavalo : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) override;
	public :
		Cavalo(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Bispo : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) override;
	public :
		Bispo(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Rainha : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) override;
	public :
		Rainha(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Rei : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) override;
	public :
		Rei(const std::filesystem::path& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
};

#include <memory>
#include <string>
#include <stdexcept>

class PeçasInstances {
public:
    static std::unique_ptr<Peça> criarPeça(const std::string& tipo, const std::filesystem::path& caminho, const sf::Vector2f& pos, Tabuleiro& tabuleiro, bool isWhite);
};

#endif
