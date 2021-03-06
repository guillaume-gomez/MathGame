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

#ifndef SCREENFINISH_H
#define SCREENFINISH_H

#include "Screen.hpp"
#include "SFML/Graphics.hpp"
#include "../constants.hpp"

#include "../libs/ResourcesManagerSFML2_1.hpp"


class ScreenFinish : public Screen
{
    public:
        ScreenFinish();
        virtual ~ScreenFinish();
        int Run(sf::RenderWindow & App);

    protected:
    private:
    	sf::Sprite m_bg;
        sf::Clock m_clock;
        std::vector<sf::String> m_stringList;
    	std::vector<sf::Text> m_textList;
    	sf::Font  m_font;
    

};

#endif // SCREENFINISH_H
