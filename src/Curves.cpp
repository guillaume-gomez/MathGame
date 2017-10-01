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

#include "Curves.hpp"

Curves::Curves(std::string function, float _begin, float _end, float step)
    :m_model(function),//function),
     m_view(m_model, Thickness, GraphScale)//, m_type(TypeObject::Curves)
{
    if(_begin != 0.0f && _end != 0.1f)
    {
        build(_begin,_end, step);
    }
}

Curves::~Curves()
{
    //dtor
}

Curves::Curves(const Curves& copy)
    : m_model(copy.m_model), m_view(m_model, Thickness, GraphScale)//, m_type(TypeObject::Curves)
{
    if(copy.m_model.m_coords.front().x != 0.0f && copy.m_model.m_coords.back().x != 0.1f)
    {
        build();
    }
}


EditorObject* Curves::clone() const
{
    return new Curves(*this);
}


std::string Curves::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << m_model.getFunction() << std::endl;
    return flux.str();
}

void Curves::draw(sf::RenderTarget& app)
{
    m_view.draw(app);
}

void Curves::drawInterval(sf::RenderTarget& app)
{
    m_view.drawInterval(app);
}

void Curves::represent(float step)
{
    m_view.represent(step);
}

void Curves::build(int _begin , int _end, float step)
{
    m_model.getRepresentativeCurve(_begin, _end, step);
    m_view.represent(step);
}

const ConstrueFunction* Curves::getModel()
{
#ifdef DEBUG
    // std::cout << "fdsfsfds" << std::endl;
#endif
    return &m_model;
}

void Curves::move(float step)
{
    if ( m_model.getChanged())
    {
        m_view.represent(step);
        m_model.setChanged(false);
    }
}

void Curves::reset()
{
    m_model.setChanged(true);
    m_model.clearFunction();
    m_view.represent(Step);
}
