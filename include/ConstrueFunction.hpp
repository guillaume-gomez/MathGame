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

#ifndef ConstrueFunction_H
#define ConstrueFunction_H

#include <cmath>
#ifdef DEBUG
#include <iostream>
#endif //DEBUG
#include <list>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
//include math librairy ( exprtk )
// see more :  "http://www.partow.net/programming/exprtk/index.html"
#include "../libs/exprtk.hpp"


#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)


class ConstrueFunction
{

    struct IntervalOfDefinition
    {
        float xStart;
        float xEnd;
    };

public:
    std::list<sf::Vector2f> m_coords;

    ConstrueFunction( std::string function = std::string() );
    ConstrueFunction(const ConstrueFunction& copy);
    std::string getFunction()const ;
    float getFunctionValue(float x) const;
    float getDerivative(float x) const;
    void getRepresentativeCurve(float _begin, float _end, float step);
    void setFunction(std::string _function);
    virtual ~ConstrueFunction();
    void manageEvent(const sf::Event &event);
    bool isDefined(float x, float* y) const;
    void setChanged(bool _changed);
    bool getChanged()const;
    bool isRepresented(float x) const;
    bool isRepresented(float x, float y) const;
    void clearFunction();

protected:
    std::string m_function;
    bool m_changed;
    std::vector<IntervalOfDefinition> intervals;
};

/***************************************** Definitions *****************************************/

inline void ConstrueFunction::setChanged(bool _changed)
{
    m_changed = _changed;
}


inline bool ConstrueFunction::getChanged() const
{
    return m_changed;
}

/***************************************** // Definitions *****************************************/

#endif // ConstrueFunction_H
