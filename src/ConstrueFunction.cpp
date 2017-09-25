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

#include "ConstrueFunction.hpp"

/**
* @brief : Constructor of the class
**/
ConstrueFunction::ConstrueFunction(std::string _function)
    :m_function(_function), m_changed(false)/*, m_scale(scale), m_begin(0.0f), m_end(0.0f), m_step(0.0f)*/
{
#ifdef DEBUG
//        std::cout << "ConstrueFunction::ConstrueFunction : " << this << std::endl;
#endif // DEBUG
}

ConstrueFunction::ConstrueFunction(const ConstrueFunction& copy)
    :m_function(copy.m_function), m_changed(copy.m_changed)
{
#ifdef DEBUG
//        std::cout << std::endl;
//        std::cout << "ConstrueFunction::ConstrueFunction(const ConstrueFunction& copy) : " << this << std::endl;
#endif // DEBUG
//    #ifdef DEBUG
//        std::cout << "ConstrueFunction::ConstrueFunction m_function : " << m_function << std::endl;
//    #endif // DEBUG
    for (auto it : copy.intervals)
    {
        intervals.push_back(it);
    }

    for (auto it : copy.m_coords)
    {
        m_coords.push_back(it);
    }
}

/**
* @brief : Destructor of the class
**/
ConstrueFunction::~ConstrueFunction()
{
    //dtor
}

/**
* @brief : Accessor of m_function
**/
std::string ConstrueFunction::getFunction() const
{
//    #ifdef DEBUG
//        std::cout << "ConstrueFunction::getFunction() : " << m_function << std::endl;
//    #endif // DEBUG
    return m_function ;
}

/**
* @brief : Accessor of m_function
* @param : the new function
**/
void ConstrueFunction::setFunction(std::string _function)
{
    m_function = _function;
    setChanged(true);
//    #ifdef DEBUG
//        std::cout << "ConstrueFunction::setFunction : " << this << " getFunction() : " << getFunction() << std::endl;
//    #endif // DEBUG
}

/**
* @brief : return the value of the function for a x
**/
float ConstrueFunction::getFunctionValue( float x) const
{
//    #ifdef DEBUG
//        std::cout << "ConstrueFunction::getFunctionValue m_function : " << m_function << std::endl;
//    #endif // DEBUG
    exprtk::symbol_table<float> symbol_table;
    symbol_table.add_variable("x",x);

    exprtk::expression<float> expression;
    expression.register_symbol_table(symbol_table);

    exprtk::parser<float> parser;
    parser.compile( m_function ,expression);

    return  expression.value();

}


float ConstrueFunction::getDerivative(float x) const
{
    exprtk::symbol_table<float> symbol_table;
    symbol_table.add_variable("x",x);

    exprtk::expression<float> expression;
    expression.register_symbol_table(symbol_table);

    exprtk::parser<float> parser;
    parser.compile(m_function, expression);
    return exprtk::derivative(expression, x);
}


void ConstrueFunction::clearFunction()
{
    m_coords.clear();
    intervals.clear();
}

/**
* @brief : Store in a vector all the value for the function
**/
void ConstrueFunction::getRepresentativeCurve(float _begin, float _end, float step)
{
    m_coords.clear();
    intervals.clear();

    int i=0;
    const float StepLimits = 100.0f;
    IntervalOfDefinition intervalTmp;
    intervalTmp.xStart = _begin;
#ifdef DEBUG
    // std::cout << _begin << "  " << _end << std::endl;
#endif
    for(float x = _begin ; x <= _end ; x += step )
    {
        float y;
        if(isDefined(x, &y))
        {
            if(i!=1)
                m_coords.push_back(sf::Vector2f(x,y));

            if(i==2)
            {
                i=3;
                x-=step;
                step/=StepLimits;
            }
            else if(i==3)
            {
                intervalTmp.xStart = x;
                i=0;
                step*=StepLimits;
            }
        }
        else if(x==_begin)
        {
            i=2;
        }
        else if(i==0)
        {
            i=1;
            x-=step;
            step/=StepLimits;
        }
        else if(i==1)
        {
            m_coords.push_back(sf::Vector2f(x-step,getFunctionValue(x-step)));
            intervalTmp.xEnd = x-step;
            intervals.push_back(intervalTmp);
            step*=StepLimits;
            i=2;
        }

    }
    intervalTmp.xEnd = _end;
    if(i!=2)
    {
        intervals.push_back(intervalTmp);
    }
}

bool ConstrueFunction::isDefined(float x, float* y) const
{
    exprtk::symbol_table<float> symbol_table;
    symbol_table.add_variable("x", x);

    exprtk::expression<float> expression;
    expression.register_symbol_table(symbol_table);

    exprtk::parser<float> parser;
    parser.compile( m_function ,expression);

    *y = expression.value();

    return((*y)==(*y)	// test si la valeur est un nombre exemple : sqrt(-5) n'existe pas, le resultat du test sera faux
           && (*y)!=std::numeric_limits<float>::infinity()
           && (*y)!=-std::numeric_limits<float>::infinity());
}

bool ConstrueFunction::isRepresented(float x) const
{
//	FOR_STL_ITERATOR(std::vector<IntervalOfDefinition>, intervals, itIntervals)
    for(IntervalOfDefinition interval : intervals)
    {
        if(x>=interval.xStart)
        {
            if(x<=interval.xEnd)
                return true;
            else
                return false;
        }
    }
    return false;
}

bool ConstrueFunction::isRepresented(float x, float y) const
{
    if(isRepresented(x) && getFunctionValue(x) == y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
