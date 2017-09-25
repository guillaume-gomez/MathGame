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

#ifndef SCREENCREDIT_H
#define SCREENCREDIT_H

#include "Screen.hpp"
#include "SFML/Graphics.hpp"
#include "../constants.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../libs/ResourcesManagerSFML2_1.hpp"



class ScreenCredit : public Screen
{
public:
    ScreenCredit();
    virtual ~ScreenCredit();
    int Run (sf::RenderWindow &App);
    void hanged();
    void handle_input(sf::Event& event);

private:
    float alpha;
    sf::Sprite m_bg;
    sf::Clock m_clock;
    sf::Clock m_clockAlpha;
    bool m_enterText;
    sf::Font  m_font;
    sf::Texture m_hanged;
    bool m_hangStart;
    sf::Sprite m_hangGui;
    unsigned int picture;
    std::vector<sf::String> m_stringList;
    std::vector<sf::Text> m_textList;
    sf::Texture m_textUnderline;
    sf::Sprite m_underline;
    sf::String m_word;
    bool m_won;
    sf::Text m_wordText;
};

#endif // SCREENCREDIT_H
