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

#ifndef IntegralModel_HPP_H
#define IntegralModel_HPP_H

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <list>
#include "../constants.hpp"
#include "ConstrueFunction.hpp"
#include "PhysicsEngine.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

namespace Physics
{
class Engine;
}

//class IntegralModel;
//
//void Physics::Engine::delIntegral(IntegralModel* integral);

class IntegralModel : public ConstrueFunction
{
//    friend class Integral;
    friend class Physics::Engine;
//    friend void Physics::Engine::delIntegral(IntegralModel* integral);
public:
    IntegralModel(std::string _function ="");
    IntegralModel(const IntegralModel& copy);
    virtual ~IntegralModel();
    void getIntegraleCurveShape(float _begin , float _end , float step);
    inline sf::Vector2f getCoordToShapes(unsigned int index ) const
    {
        if(m_listCoordShapes.size())
            return m_listCoordShapes[index];
        else
            return sf::Vector2f(0.0f,0.0f);
    }
    inline unsigned int getNbPoints () const
    {
        return m_listCoordShapes.size();
    }
    inline unsigned int getNbCoordByShape(unsigned int index) const
    {
        if(index < m_nbCoordByShape.size())
            return m_nbCoordByShape[index];
        else
            return 0U;
    }
//        void showPoints();
    sf::Vector2f getBegin() const;
    sf::Vector2f getEnd() const;
    bool inPhysicsEngine() const;
private:
    std::vector<sf::Vector2f> m_listCoordShapes;
    std::vector<unsigned int> m_nbCoordByShape;

    bool m_inPhysicsEngine;
};

inline sf::Vector2f IntegralModel::getBegin() const
{
    if(m_listCoordShapes.size() > 0)
    {
        return m_listCoordShapes.front();
    }
    else
    {
        std::runtime_error("IntegralModel::getBegin() : the array is empty");
        return sf::Vector2f(0.0f,0.0f);
    }
}

inline sf::Vector2f IntegralModel::getEnd() const
{
    if(m_listCoordShapes.size() > 0)
    {
        return m_listCoordShapes.back();
    }
    else
    {
        std::runtime_error("IntegralModel::getBegin() : the array is empty");
        return sf::Vector2f(0.0f,0.0f);
    }
}

inline bool IntegralModel::inPhysicsEngine() const
{
    return m_inPhysicsEngine;
}

#endif // IntegralModel_HPP_H
