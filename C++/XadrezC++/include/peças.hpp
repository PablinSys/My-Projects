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
		virtual bool analisarMovimento(const sf::Vector2i& new_pos)  = 0;
	public : 
		bool isBranco;
		sf::Vector2i positionIndex;
		Peça(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco);
		bool addNewPos(int x, int y, bool isMoviment) override;
		~Peça();
};
class Peao : public Peça
{
	protected :
		bool analisarMovimento(const sf::Vector2i& new_pos)  override;
	private :
		bool primeiroLance = true;
	public :
		Peao(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco, const bool& primeiroLance = true);
};
class Torre : virtual public Peça
{
	protected :
		bool analisarMovimento(const sf::Vector2i& new_pos)  override;
	private :
		bool _; // migué
	public :
		Torre(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Cavalo : public Peça
{
	protected :
		bool analisarMovimento(const sf::Vector2i& new_pos)  override;
	public :
		Cavalo(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Bispo : virtual public Peça
{
	protected :
		bool analisarMovimento(const sf::Vector2i& new_pos)  override;
	bool __; // migué
	public :
		Bispo(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Rainha : public Bispo, public Torre
{
	protected :
		bool analisarMovimento(const sf::Vector2i& new_pos)  override;
	public :
		Rainha(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco);
};
class Rei : public Peça
{
	protected :
		bool analisarMovimento(const sf::Vector2i& new_pos)  override;
	public :
		Rei(const std::filesystem::path& path_img, const sf::Vector2f& position, const sf::Vector2i indexPosition, Tabuleiro& tabuleiro, const bool& isBranco);
};

#include <memory>
#include <string>
#include <stdexcept>

class PeçasInstances {
public:
    static std::unique_ptr<Peça> criarPeça(const std::type_info& tipo, const std::filesystem::path& caminho, const sf::Vector2f& pos, const sf::Vector2i& indexpos, Tabuleiro& tabuleiro, bool isWhite);
};

#endif
