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

#include "Point.hpp"
#include <sstream>


Point::Point(float radius,bool goalPoint, float scale)
    :EditorCircle(), m_goalPoint(goalPoint)
{
    if(m_goalPoint)
    {
        this->m_type = TypeObject::GoalPoint;
        this->setFillColor(sf::Color(255, 0, 0));
//        std::cout << "Colored in the class point" << std::endl;
    }
    else
    {
        this->m_type = TypeObject::Point;
        this->setFillColor(sf::Color(0, 0, 0));
//        std::cout << "UnColored in the class point" << std::endl;
    }
    this->setRadius(radius);
    this->setOrigin(radius, radius);
    this->setScale(GraphScale, GraphScale);
}

Point::Point(const Point& original)
    :EditorCircle(original), m_goalPoint(original.m_goalPoint)
{
    if(m_goalPoint)
    {
        this->m_type = TypeObject::GoalPoint;
        this->setFillColor(sf::Color(255, 0, 0));
//        std::cout << "Colored in the class point" << std::endl;
    }
    else
    {
        this->m_type = TypeObject::Point;
        this->setFillColor(sf::Color(0, 0, 0));
//        std::cout << "UnColored in the class point" << std::endl;
    }
    this->setRadius(original.getRadius());
    this->setOrigin(original.getRadius(), original.getRadius());
    this->setScale(GraphScale, GraphScale);
}

EditorObject* Point::clone() const
{
    return new Point(*this);
}

Point::Point()
{

}

std::string Point::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << EditorCircle::save(scale);
    return flux.str();
}

EditorObject* Point::loadView(const Element& elmt, float scale)
{
    Point * NewPoint =  new Point(sizePoint);
    NewPoint->setPosition(elmt.getCoord().x * scale/*- widthTex*/ , - elmt.getCoord().y * scale/* - heightTex*/);
    return NewPoint;
}

Point::~Point()
{
    //dtor
}

