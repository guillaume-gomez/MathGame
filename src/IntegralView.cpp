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

#include "IntegralView.hpp"


IntegralView::IntegralView(IntegralModel& model, const float scale)
    : m_model(model), m_scale(scale)
{}

IntegralView::~IntegralView()
{
    //dtor
}

void IntegralView::representShape()
{
    unsigned int index = 0;
    unsigned int i = 0;

    while (i < m_model.getNbPoints() )
    {
        thor::ConcaveShape temp;
        temp.setPointCount(m_model.getNbCoordByShape(index));
        for (unsigned int j = 0; j < m_model.getNbCoordByShape(index); j++)
        {
            temp.setPoint(j, sf::Vector2f(m_model.getCoordToShapes(i).x * m_scale, - m_model.getCoordToShapes(i).y * m_scale));
            //add the scale
            i++;
        }
        // TEMP
        temp.setFillColor(sf::Color(23,20,20,100));
        temp.setOutlineColor(sf::Color(0,0,0));
        temp.setOutlineThickness(1);

        if(temp.getPointCount() > 2)
        {
            m_shapeList.push_back(temp);
        }
        index++;
    }
}

void IntegralView::representLine()
{
    unsigned int index = 0;
    unsigned int i = 0;

    while (i < m_model.getNbPoints() )
    {
        sf::RectangleShape temp;

        for (unsigned int j = 0; j < m_model.getNbCoordByShape(index); j++)
        {
            temp.setPosition(m_model.getCoordToShapes(i).x * m_scale, - m_model.getCoordToShapes(i).y * m_scale);
            temp.setSize(sf::Vector2f(200*m_scale,10*m_scale));
            //add the scale
            i++;
        }
        // TEMP
        temp.setFillColor(sf::Color(23,20+10*index,20+50*index,100));
        temp.setOutlineColor(sf::Color(0,0,0));
        temp.setOutlineThickness(1);
        // temp.setPosition(10, 20);
        m_lineList.push_back(temp);
        index++;
    }
}


void IntegralView::drawShape(sf::RenderTarget& target)
{
    for (unsigned int i = 0 ; i < m_shapeList.size() ; i++)
    {
        target.draw(m_shapeList[i]);
    }
}

void IntegralView::drawLine(sf::RenderTarget& target)
{
    for (unsigned int i = 0 ; i < m_lineList.size() ; i++)
    {
        target.draw(m_lineList[i]);
    }
}

