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

#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <stdexcept>
#include <sstream>

#include "../constants.hpp"
#include "EditorObject.hpp"
#include "IntegralModel.hpp"
#include "IntegralView.hpp"


/// for the moment, only the shape representation is possible
class Integral : public EditorObject
{
public:
    Integral(std::string function = "0", float _begin = 0.0f, float _end = 0.1f, float step = Step);
    virtual ~Integral();
    Integral(const Integral& other);
    virtual EditorObject* clone() const ;
    virtual std::string save(float scale = GraphScale) const ;
    virtual void draw(sf::RenderTarget& app);
    void build(int _begin = - MaxSizeGraph, int _end = MaxSizeGraph, float step = Step);
    std::string getFunction() const;
    void setFunction(std::string str);

private:
    virtual void setPosition(sf::Vector2f& position);
    virtual void setPosition(float x, float y);
    virtual sf::FloatRect get_GlobalBounds() const ;
    virtual sf::Vector2f get_Position() const;
    virtual EditorObject* loadView(const Element& elmt, float scale);

    IntegralModel m_model;
    IntegralView m_view;
};

inline EditorObject* Integral::loadView(const Element& elmt, float scale)
{
#ifdef DEBUG
    std::cerr << "nothing to do for the moment";
#endif
    return nullptr;
}

inline void Integral::setPosition(sf::Vector2f& position)
{
    std::runtime_error("In the class Integral::setPosition -> nothing to do");
}


inline void Integral::setPosition(float x, float y)
{
    std::runtime_error("In the class Integral::setPosition -> nothing to do");
}


inline sf::FloatRect Integral::get_GlobalBounds() const
{
    std::runtime_error("In the class Integral::get_GlobalBounds -> nothing to do");
    return sf::FloatRect();
}

inline sf::Vector2f Integral::get_Position() const
{
    std::runtime_error("In the class Integral::get_Position -> nothing to do");
    return sf::Vector2f();
}

inline std::string Integral::getFunction() const
{
    return m_model.getFunction();
}

inline void Integral::setFunction(std::string str)
{
    m_model.setFunction(str);
}

#endif // INTEGRAL_H
