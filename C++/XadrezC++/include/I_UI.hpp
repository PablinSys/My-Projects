#ifndef INTERFACE_UI_H
#define INTERFACE_UI_H

#include <string>
#include <SFML/Graphics.hpp>
template <typename T>
class I_UI
{ 
    protected : 
        T* objectUI;
    public:
        sf::Vector2f position;
        virtual bool addNewPos(int x, int y, bool isMoviment) = 0;
        bool addNewPos(int inde_x, int index_y, sf::Vector2f new_position);
        virtual void draw(sf::RenderWindow* window);
};

#endif