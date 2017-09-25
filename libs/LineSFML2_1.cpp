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

#include "LineSFML2_1.hpp"

LineSFML2_1::LineSFML2_1(const sf::Vector2f& startCoords, const sf::Vector2f& endCoords)
    :m_startCoords(startCoords), m_endCoords(endCoords)
{
    compute();
    setThickness(1);
}
LineSFML2_1::~LineSFML2_1()
{

}
LineSFML2_1::LineSFML2_1(const LineSFML2_1& other)
{
    m_startCoords=other.m_startCoords;
    m_endCoords=other.m_endCoords;
    m_length=other.m_length;
    m_thickness=other.m_thickness;
}
LineSFML2_1& LineSFML2_1::operator=(const LineSFML2_1& other)
{
    m_startCoords=other.m_startCoords;
    m_endCoords=other.m_endCoords;
    m_length=other.m_length;
    m_thickness=other.m_thickness;

    return *this;
}

void LineSFML2_1::compute()
{
    m_length = sqrt(pow(m_endCoords.x-m_startCoords.x,2)+pow(m_endCoords.y-m_startCoords.y,2));
#ifdef DEBUG
//        // // std::cout << "m_length : " << m_length << std::endl;
#endif // DEBUG
    setSize(sf::Vector2f(getLength(),getThickness()));
    setPosition(getStartCoords());
    setRotation(atan2(m_endCoords.y-m_startCoords.y, m_endCoords.x-m_startCoords.x)*180/M_PI);
}
