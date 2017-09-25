/*
 *  A 2D video game in C++ with SFML where platforms are actually Maths Curves resulting of equations you write
 *  Copyright (C) 2013,2017  Gomez Guillaume, Jarretier Adrien
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.*
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact us on Github : https://github.com/guillaume-gomez/MathGame
 *                      or https://github.com/AdrienJarretier
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <SFGUI/SFGUI.hpp>
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
