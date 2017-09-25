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

#include "Integral.hpp"

Integral::Integral(std::string function, float _begin, float _end, float step)
    :m_model(function),//function),
     m_view(m_model, GraphScale)//, m_type(TypeObject::Integral)
{
    if(_begin != 0.0f && _end != 0.1f)
    {
        build(_begin,_end, step);
    }
}

Integral::~Integral()
{
    //dtor
}

Integral::Integral(const Integral& copy)
    : m_model(copy.m_model), m_view(m_model,GraphScale)//, m_type(TypeObject::Integral)
{

}


EditorObject* Integral::clone() const
{
//    #ifdef DEBUG
//        std::cout << "EditorObject* Integral::clone() const" << std::endl;
//    #endif // DEBUG
    return new Integral(*this);
}


std::string Integral::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << m_model.getFunction() << std::endl;
    flux << m_model.getBegin().x << std::endl;
    flux << m_model.getEnd().x << std::endl;
    return flux.str();
}

void Integral::draw(sf::RenderTarget& app)
{
    m_view.drawShape(app);
}

void Integral::build(int _begin , int _end, float step)
{
    m_model.getIntegraleCurveShape(_begin, _end, Step);
    m_view.representShape();
}
