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

#include "GraphView.hpp"

GraphView::GraphView(ConstrueFunction& model,float thickness, float scale)
    :m_isStandAlone(false), m_model(&model),m_thickness(thickness), m_scale(scale), m_graphColor(sf::Color(50,67,135)),
     m_viewport(sf::View())
{}

GraphView::GraphView(float thickness, float scale)
    : m_isStandAlone(true), m_model(nullptr), m_thickness(thickness), m_scale(scale), m_graphColor(sf::Color(50,67,135)),
      m_viewport(sf::View())
{

}

GraphView::~GraphView()
{
    //dtor
}

void GraphView::represent(float step)
{
    standAloneRepresent(*(this->m_model), step);
}

void GraphView::standAloneRepresent(const ConstrueFunction& model, float step)
{
    m_lines.clear();

    std::list<sf::Vector2f>::const_iterator it = model.m_coords.begin();
    std::list<sf::Vector2f>::const_iterator itNext = model.m_coords.begin();

    if(itNext!=model.m_coords.end())
    {
        itNext++;
    }

    while(itNext!=model.m_coords.end())
    {
        if((itNext->x - it->x) <= step * 2)
        {
            m_lines.push_back(LineSFML2_1(sf::Vector2f(it->x, -it->y) * m_scale, sf::Vector2f(itNext->x, -itNext->y) * m_scale));
            m_lines.rbegin()->setFillColor(m_graphColor);
            m_lines.rbegin()->setThickness(m_thickness);
        }
        it++;
        itNext++;
    }
}

void GraphView::draw(sf::RenderTarget& App)
{
    FOR_STL_ITERATOR(std::list<LineSFML2_1>, m_lines, itl)
    {
        if( itl->getPosition().x >= m_viewport.getCenter().x - m_viewport.getSize().x/2
                &&  itl->getPosition().x <= m_viewport.getCenter().x + m_viewport.getSize().x/2 )
        {
            App.draw(*itl);
        }
    }
}


void GraphView::drawInterval(sf::RenderTarget& App, unsigned int split)
{
    unsigned int increment = 0;
    FOR_STL_ITERATOR(std::list<LineSFML2_1>, m_lines, itl)
    {
        if(increment == split)
        {
            App.draw(*itl);
            increment = 0;

        }
        increment++;
    }
}
