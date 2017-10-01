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

#ifndef CURSOR_H
#define CURSOR_H

#include "AbstractCursor.hpp"
#include "Button.hpp"

class Cursor : public AbstractCursor
{
    sf::RectangleShape	shape;
public:
    // Constructeurs
    Cursor(sf::Color color = sf::Color::White , unsigned int thick = 1,AbstractWidget * first = 0 );
    void setSize ( sf::Vector2f );
    Button* getButton();

    // Fonctions de la classe
    virtual void Calculate(float time_interval);
    virtual void Draw(sf::RenderTarget & target, float alpha = 1.f);
    sf::Vector2f GetPosition() const
    {
        return shape.getPosition();
    };
};

#endif
