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

#include "ManageFunctions.hpp"

ManageFunctions::ManageFunctions()
    :m_changed(false), m_currentIndex(0), m_view(sf::View())
{
    //ctor
}

ManageFunctions::~ManageFunctions()
{
    //dto
}


void ManageFunctions::handle_input(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {

        case sf::Keyboard::P:
            m_currentIndex++;
            m_changed = true;
            if (m_currentIndex >= m_vectorCurves.size())
            {
                m_currentIndex = 0;
            }
            colorize();
            break;

        case sf::Keyboard::M:

            m_changed = true;
            if( m_currentIndex == 0)
            {
                m_currentIndex = m_vectorCurves.size() - 1;
            }
            else
            {
                m_currentIndex--;
            }
            colorize();
            break;

        default:
            break;
        }
    }

}

void ManageFunctions::represent(float step)
{
    if(m_changed)
    {
        //// std::cout << "Represent " << m_currentIndex << std::endl;
        m_vectorCurves.at(m_currentIndex).represent(step);
        m_changed = false;
    }
}

const ConstrueFunction* ManageFunctions::getModelIndex()
{
    return m_vectorCurves.at(m_currentIndex).getModel();
}

void ManageFunctions::colorize()
{
    showBefore();
    m_vectorCurves.at(m_currentIndex).setColor(CurveColor);
    showAfter();
}

bool ManageFunctions::showBefore()
{
    if( m_currentIndex - 1 < 0)
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex - 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex - 1).setColor(PreviousCurveColor);
    }
    return true;
}

bool ManageFunctions::drawBefore(sf::RenderTarget& app)
{
    if( m_currentIndex - 1 < 0)
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex - 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex - 1).drawInterval(app);
    }
    return true;
}

bool ManageFunctions::showAfter()
{
    if( (m_currentIndex + 1) >= m_vectorCurves.size())
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex + 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex + 1).setColor(NextCurveColor);
    }
    return true;
}

bool ManageFunctions::drawAfter(sf::RenderTarget& app)
{
    if( (m_currentIndex + 1) >= m_vectorCurves.size())
    {
        return false;
    }
    else
    {
        //m_vectorCurves.at(m_currentIndex + 1).receiveView(m_view);
        m_vectorCurves.at(m_currentIndex + 1).drawInterval(app);
    }
    return true;
}


void ManageFunctions::draw(sf::RenderTarget& app)
{
    drawBefore(app);
    m_vectorCurves.at(m_currentIndex).receiveView(m_view);
    m_vectorCurves.at(m_currentIndex).draw(app);
    drawAfter(app);
}


void ManageFunctions::setViews(const sf::View view)
{
    m_view = view;
}

void ManageFunctions::addFunction(std::string function)
{
    Curves newFunction(function);
    m_vectorCurves.push_back(newFunction);

}


void ManageFunctions::reset()
{
//std::cout << "clearManageFunctions" << std::endl;
    m_changed = true;
    m_vectorCurves.clear();
//    m_graphModel.clearFunction();
}

void ManageFunctions::resetToZero()
{
    m_currentIndex = 0;
    colorize();
}
