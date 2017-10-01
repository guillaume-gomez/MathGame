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

#ifndef MENU_H
#define MENU_H

#include "AbstractPanel.hpp"

class Menu : public AbstractPanel
{
    virtual void OnDisplay(bool entering);
    virtual void OnHide(bool entering);
public:
    Menu(AbstractCursor * cursor, AbstractPanel * parent = 0);  // On doit pouvoir faire passer le curseur utilisé pour le panel.
    virtual void Calculate(float time_interval);
    virtual void Draw(sf::RenderTarget & target,float alpha = 1.f);
    void handle_input(sf::Event& event);

    bool m_down;
    bool m_up;
    bool m_right;
    bool m_left;


};

#endif
