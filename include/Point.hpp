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

#ifndef POINT_H
#define POINT_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "EditorCircle.hpp"
#include "../constants.hpp"
#include "../files.hpp"


class Point : public EditorCircle
{
public:
    Point();
    Point(float radius = 1.0f,bool goalPoint = false, float scale = GraphScale);
    Point(const Point& original);
    virtual ~Point();
    inline bool isGoal() const
    {
        return m_goalPoint;
    }
    virtual EditorObject* clone() const;
    virtual std::string save(float scale = GraphScale) const;
    EditorObject* loadView(const Element& elmt, float scale);
protected:
    //if is the final point
    bool m_goalPoint;
private:
};

#endif // POINT_H
