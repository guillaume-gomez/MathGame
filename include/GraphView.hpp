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

#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <list>
#include <vector>
#include <limits>

#include <SFML/Graphics.hpp>

#include "ConstrueFunction.hpp"
#include "../libs/LineSFML2_1.hpp"
#include "../constants.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)


class GraphView
{
public:
    GraphView( ConstrueFunction& model, float thickness = 1.0f, float scale = 1.0f);
    GraphView(float thickness = 1.0f, float scale = 1.0F);
    virtual ~GraphView();
    void represent(float step);

    void draw(sf::RenderTarget& App );
    void drawInterval(sf::RenderTarget& App, unsigned int split = 2);
    void setGraphColor(const sf::Color& graphColor);
    void standAloneRepresent(const ConstrueFunction& function, float step);
    void receiveView(const sf::View view);

private:
    GraphView(const GraphView& copy);
    //without only one model
    const bool m_isStandAlone;
    std::list<LineSFML2_1> m_lines;
    const ConstrueFunction* m_model;
    float m_thickness;
    float m_scale;
    sf::Color m_graphColor;
    sf::View m_viewport;
};

/**
*  accessors
**/

inline void GraphView::setGraphColor(const sf::Color& graphColor)
{
    m_graphColor = graphColor;
    if(!m_lines.empty())
    {
        FOR_STL_ITERATOR(std::list<LineSFML2_1>, m_lines, itl)
        {
            itl->setFillColor(m_graphColor);
        }
    }
}

inline void GraphView::receiveView(const sf::View view)
{
    m_viewport = view;
}
#endif // GRAPHVIEW_H
