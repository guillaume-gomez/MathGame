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

#include "IntegralModel.hpp"

IntegralModel::IntegralModel(std::string _function)
    :ConstrueFunction(_function), m_inPhysicsEngine(false)
{
//    #ifdef DEBUG
//        std::cout << "IntegralModel::IntegralModel (ctor) : " << this << std::endl;
//    #endif // DEBUG
}

IntegralModel::IntegralModel(const IntegralModel& copy)
    :ConstrueFunction(copy.getFunction()), m_inPhysicsEngine(false)
{
    for(auto it : copy.m_listCoordShapes)
    {
        m_listCoordShapes.push_back(it);
    }

    for(auto it : copy.m_nbCoordByShape)
    {
        m_nbCoordByShape.push_back(it);
    }
//    #ifdef DEBUG
//        std::cout << "IntegralModel::IntegralModel (copy ctor) : " << this << " m_function : " << m_function<< std::endl;
//    #endif // DEBUG
    Physics::Engine::getEngine()->addIntegral(this);
    m_inPhysicsEngine = true;
}

void IntegralModel::getIntegraleCurveShape(float _begin , float _end , float step)
{
    std::list<sf::Vector2f>::iterator firstPoint = m_coords.begin();
    //detect where the function cuts the abscissa
    int sign = (firstPoint->y >= 0)? 1 : -1;

    getRepresentativeCurve(_begin,_end,step);
    sf::Vector2f fbegin (m_coords.front());
    m_coords.push_front(sf::Vector2f(fbegin.x,0.0f));
    sf::Vector2f fend = m_coords.back();
    m_coords.push_back(sf::Vector2f(fend.x,0.0f));

    bool addList = false;
    std::list<sf::Vector2f>::iterator it = m_coords.begin();
    std::list<sf::Vector2f>::iterator itNext = m_coords.begin();
    itNext++;

    sf::Vector2f coordZero;
    while(it != m_coords.end())
    {
        addList = false;
        unsigned int nbCoord = 0;
        if (sign == 0)
        {
            m_listCoordShapes.push_back(coordZero);
            nbCoord++;
        }
        //while the curve stay on or down the abscissa
        while(it != m_coords.end() && !addList)
        {
            if( itNext != m_coords.end())
            {
                if( it->y > 0.0f && itNext->y <= 0.0f)
                {
                    // if the sign had changed
                    addList = true;
                    sign = 1;
                }
                else if (it->y < 0.0f && itNext->y >= 0.0f)
                {
                    addList = true;
                    sign = -1;
                }
                else if ( it->y == 0.0f)
                {
                    coordZero = (*it);
                    addList = true;
                    sign = 0;
                }
                //// std::cout << "X " << itNext->x << " Y " << itNext->y << std::endl;
            }
            m_listCoordShapes.push_back(*it);
            nbCoord++;
            it++;
            itNext++;
        }
        // a point is added if the curve doesn't cut the abscissa at 0 with the step
        // a second point is added to fill the future shape in IntegralView
        if(sign != 0)
        {
            coordZero = sf::Vector2f(it->x, 0.0f);
            m_listCoordShapes.push_back(coordZero);
            nbCoord++;
            sign = 0;
        }
        //to detect the end of a shape
        m_nbCoordByShape.push_back(nbCoord);
    }
}

//
//void IntegralModel::showPoints()
//{
////    #ifdef DEBUG
////        unsigned int index = 0;
////        // std::cout << "-----------------Coord---------------" << std::endl;
//////        for (auto it : m_listCoordShapes)
//////        {
//////            // std::cout <<"("<< it.x << ", " << it.y <<")" << std::endl;
//////        }
////        // std::cout << "------------------------------------" << std::endl;
////    #endif
//}

IntegralModel::~IntegralModel()
{
    if(m_inPhysicsEngine)
    {
        Physics::Engine::getEngine()->delIntegral(this);
        m_inPhysicsEngine = false;
    }
}

/*
 void IntegralModelOld::getIntegraleCurve(float _begin , float _end , float step)
 {
    getRepresentativeCurve(_begin,_end,step);
    //
    /sf::Vector2f fbegin (m_coords.front());

    m_coords.push_front(sf::Vector2f(fbegin.x,0.0f));

    sf::Vector2f fend = m_coords.back();
    m_coords.push_back(sf::Vector2f(fend.x,0.0f));


    #ifdef DEBUG
		FOR_STL_ITERATOR(std::list<sf::Vector2f>, m_coords, it)
        {
            // std::cout <<" x : "<< it->x << " y : " << it->y << std::endl;
        }
    #endif // DEBUG

 }
*/
