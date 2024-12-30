#include "../include/I_UI.hpp"
#include <stdexcept>

template<>
void I_UI<sf::VertexArray>::draw(sf::RenderWindow* window)
{
    window->draw(objectUI);
}
template <>
void I_UI<sf::Sprite>::draw(sf::RenderWindow* window)
{
    window->draw(objectUI);
}
template <typename T>
inline void I_UI<T>::draw(sf::RenderWindow* window)
{
    throw std::runtime_error("TIPO INVÁLIDO PARA DESENHAR");
}