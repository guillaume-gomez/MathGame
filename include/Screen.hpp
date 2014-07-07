#ifndef SCREEN_H
#define SCREEN_H

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Screens.hpp"

class Screen
{
    public:
        Screen();
        virtual ~Screen();
        virtual int Run ( sf::RenderWindow &App) = 0;

    protected:
        sfg::Desktop m_desktop;
};

#endif // SCREEN_H
