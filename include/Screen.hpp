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

    protected:
        sf::View m_viewport;
};

#endif // SCREEN_H
