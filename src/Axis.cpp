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

#include <SFML/Graphics.hpp>
#include <vector>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include "Axis.hpp"


#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)
#define FOR_STL_REVERSE_ITERATOR(container_type, name, iteratorName) for(container_type::reverse_iterator iteratorName=name.rbegin(); iteratorName!=name.rend(); iteratorName++)


/**
* @brief : Constructor of the class
**/
Axis::Axis(float _graduation)
    :m_originyAxis(0.0f), m_originxAxis(0.0f), m_scale(1.0f), m_graduation(_graduation), m_view(sf::View())
{
    sf::Color color(18, 25, 112, 75);
    float heightAxis = 4.0f;
    float widthAxis = 2000.0f;
    int nbGraduation = (int) widthAxis / m_graduation;

    float heightGrad = 10.0f;
    float widthGrad = 2.0f;
    float _x = -1000.0f;
    float _y = 0.0f - heightGrad / 2.0f ;

    ////////////////////////////////////////////////////////
    // XAxis Graduation
    for (int i = 0 ; i < nbGraduation / 2 ; i++)
    {
        sf::RectangleShape temp(sf::Vector2f(widthGrad, heightGrad));
        temp.setPosition(_x - widthGrad / 2.0f, _y);
        temp.setFillColor(color);
        m_listXGrad.push_back(temp);
        _x +=  m_graduation;
    }

    for (int i = 0 ; i < nbGraduation / 2 ; i++)
    {
        sf::RectangleShape temp(sf::Vector2f(widthGrad, heightGrad));
        temp.setPosition(_x - widthGrad / 2.0f, _y);
        temp.setFillColor(color);
        m_listXGrad.push_back(temp);
        _x +=  m_graduation;
    }
    //
    ///////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////
    // YAxis Graduation
    _y = -1000.0f;
    _x = 0.0f - heightGrad / 2.0f ;
    for (int i = 0 ; i < nbGraduation / 2  ; i++)
    {
        sf::RectangleShape temp(sf::Vector2f(heightGrad, widthGrad));
        temp.setPosition(_x, _y - widthGrad / 2.0f);
        temp.setFillColor(color);
        m_listYGrad.push_back(temp);
        _y +=  m_graduation;
    }
    _y += m_graduation;
    for (int i = 0 ; i < nbGraduation / 2  ; i++)
    {
        sf::RectangleShape temp(sf::Vector2f(heightGrad, widthGrad));
        temp.setPosition(_x, _y - widthGrad / 2.0f);
        temp.setFillColor(color);
        m_listYGrad.push_back(temp);
        _y +=  m_graduation;
    }
    //
    ////////////////////////////////////////////////////////



    /////////////////////////////////////////////
    // xAxis
    m_shapexAxis.setSize(sf::Vector2f(widthAxis, heightAxis));
    m_shapexAxis.setPosition(-1000.0f, -heightAxis / 2);
    m_shapexAxis.setFillColor(color);
    //
    /////////////////////////////////////////////////

    /////////////////////////////////////////////////
    //
    m_shapeyAxis.setSize(sf::Vector2f(heightAxis, widthAxis));
    m_shapeyAxis.setPosition(-heightAxis / 2, -1000.0f);
    m_shapeyAxis.setFillColor(color);
    // yAxis
    /////////////////////////////////////////////////

}

/**
* @brief : Destructor of the class
**/
Axis::~Axis()
{
    //dtor
}

/**
* @brief : Accessor of xAxis
**/
int Axis::getxAxis()
{
    return m_originxAxis;
}

/**
* @brief : Accessor of yAxis
**/
int Axis::getyAxis()
{
    return m_originyAxis;
}

/**
* @brief : Accessor of scale
**/
float Axis::getScale()
{
    return m_scale;
}


void Axis::setGraduation(float _graduation)
{
    m_graduation = _graduation;
}

float Axis::getGraducation()
{
    return m_graduation;
}

/**
* @brief : Draw
**/
void Axis::draw(sf::RenderWindow& App)
{

    FOR_STL_ITERATOR(std::vector<sf::RectangleShape>, m_listXGrad, it)
    {
        if( it->getPosition().x >= m_view.getCenter().x - m_view.getSize().x
                &&  it->getPosition().x <= m_view.getCenter().x + m_view.getSize().x)
        {
            App.draw(*it);
        }
    }

    //
    FOR_STL_ITERATOR(std::vector<sf::RectangleShape>, m_listYGrad, it)
    {
        if( it->getPosition().y >= m_view.getCenter().y - m_view.getSize().y/2
                &&  it->getPosition().y <= m_view.getCenter().y + m_view.getSize().y/2 )
        {
            App.draw(*it);
        }
    }
    App.draw(m_shapexAxis);
    App.draw(m_shapeyAxis);
}
