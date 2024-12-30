#ifndef PEÇAS_H
#define PEÇAS_H

#include "I_UI.hpp"
#include "tabuleiro.hpp"
class Peça : public I_UI<sf::Sprite> //classe abstrata
{
	protected :
		sf::Texture peça_img;
		Tabuleiro* tab;
		bool isBranco;
		virtual bool analisarMovimento(const sf::Vector2f& pos) = 0;
	public : 
		Peça(const std::string& path_img, const sf::Vector2f& position, Tabuleiro& tabuleiro, const bool& isBranco);
		bool addNewPos(int x, int y) override;
		~Peça();
};
class Peao : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) override;
	public :
};
class Torre : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) = 0;
	public :
};
class Cavalo : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) = 0;
	public :
};
class Bispo : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) = 0;
	public :
};
class Rainha : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) = 0;
	public :
};
class Rei : public Peça
{
	bool analisarMovimento(const sf::Vector2f& pos) = 0;
	public :
};
#endif
