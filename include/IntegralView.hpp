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

#ifndef IntegralView_H
#define IntegralView_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <list>
#include <vector>

#include <Thor/Shapes.hpp>

#include "IntegralModel.hpp"


class IntegralView
{
public:
    IntegralView(IntegralModel& model ,const float scale );
    IntegralView();
    virtual ~IntegralView();
    void drawShape(sf::RenderTarget& target);
    void drawLine(sf::RenderTarget& target);
    void representLine();
    void representShape();
private:
    IntegralView(const IntegralView& copy);

    const IntegralModel& m_model;
    std::vector<sf::RectangleShape> m_lineList;
    std::vector<thor::ConcaveShape> m_shapeList;
    float m_scale;
};

#endif // IntegralView_H
