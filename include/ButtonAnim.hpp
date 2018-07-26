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

#ifndef BUTTONANIM_H
#define BUTTONANIM_H

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include "AniSprite.hpp"
#include "StaticButton.hpp"


class ButtonAnim : public StaticButton
{
    public:
        ButtonAnim(const char* _filename = "", int _widthFrame=0, int _heigtFrame=0);
        virtual ~ButtonAnim();
        void switchTile();
        void handle_input(sf::Event& event, sf::RenderTarget& target);
        void Launch();

    private:
        //to launch animation for instance;
        bool m_changing;
        AniSprite m_spriteList;
        sf::Texture m_texture;
};
#endif // BUTTONANIM_H
