#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Screens.hpp"

class Screen
{
    public:
        Screen();
        virtual ~Screen();
        virtual int Run ( sf::RenderWindow &App) = 0;
};

#endif // SCREEN_H
