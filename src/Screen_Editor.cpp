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

#include "Screen_Editor.hpp"

Screen_Editor::Screen_Editor(sf::RenderWindow& App, ScreenLink* link)
    :m_editor(App), m_link(link)
{
    recenterCamera();
}

Screen_Editor::~Screen_Editor()
{
    //dtor
}

int Screen_Editor::Run(sf::RenderWindow& App)
{
    bool Running = true;
    m_editor.setBack(false);
    m_editor.setCenterCamera();
    m_editor.setSaving(false);


    while(Running)
    {
        Running =  m_editor.handleInput();

        if(m_editor.isBacked())
        {
            recenterCamera();
            Running = false;
            return MENU;
        }
        m_editor.move();
        m_editor.save(m_link);
        m_editor.show();
        m_editor.draw();
        App.display();
    }
    return (SCREEN_EXIT);
}

void Screen_Editor::recenterCamera()
{
    sf::View   viewPerso = m_editor.m_app.getView();
    viewPerso.reset(sf::FloatRect(0, 0, WindowWidth, WindowHeight));
    m_editor.m_app.setView(viewPerso);
}
