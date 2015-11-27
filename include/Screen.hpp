#ifndef SCREEN_H
#define SCREEN_H

#include <SFGUI/Desktop.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../files.hpp"
#include "Screens.hpp"

class Screen
{
    public:
        Screen();
        virtual ~Screen();
        virtual int Run ( sf::RenderWindow &App) = 0;

    protected:
        sfg::Desktop m_desktop;
        static bool isloadTheme;
};

#endif // SCREEN_H
