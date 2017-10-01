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

#include "GravityCircle.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>

GravityCircle::GravityCircle(float _radius, float radiusMax, bool defOriginCenter, std::string filename)
    :EditorCircle(), m_filename(filename),m_radiusMax(radiusMax), m_texture(*TextureManager::getTextureManager()->getResource(FilenameSmileyTex))
{
//    #ifdef DEBUG
//        std::cout << "*****GravityCircle::GravityCircle::m_physicsCircle : " << &(getPhysicsCircle()) <<  std::endl;
//    #endif // DEBUG
    if(_radius > 0.0f)
    {
        this->m_type = TypeObject::Circle;
        this->setRadius(_radius);
        if(defOriginCenter)
        {
            this->setOrigin(_radius,_radius);
        }

        if(radiusMax < _radius)
        {
            radiusMax = _radius;
        }

        this->setTexture(&m_texture);
//        m_physicsCircle.setAsGravityCircle();
    }
    else
    {
        throw std::runtime_error("An instance of GravityCircle can't be created because the radius is equal to zero");
    }
}

GravityCircle::GravityCircle(const GravityCircle& original)
    :EditorCircle(original), m_filename(original.m_filename),m_radiusMax(original.m_radiusMax),
     m_texture(original.m_texture)
{
//    #ifdef DEBUG
//        std::cout << "*****GravityCircle::GravityCircleCOPYYYYYYYYYY::m_physicsCircle : " << &(getPhysicsCircle()) <<  std::endl;
//    #endif // DEBUG

    this->setTexture(&m_texture);
    m_physicsCircle.setAsGravityCircle();
}

void GravityCircle::grow(float step)
{
    float currentRadius = this->getRadius();
    if(currentRadius < m_radiusMax)
    {
        this->setRadius(currentRadius + step);
        this->setOrigin(currentRadius + step,currentRadius + step);
    }
}

std::string GravityCircle::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << this->getRadius() << std::endl;
    flux << EditorCircle::save(scale);
    return flux.str();
}

EditorObject* GravityCircle::loadView(const Element& elmt, float scale)
{
    GravityCircle * NewCircle =  new GravityCircle();
    NewCircle->setRadius(elmt.getRadius());
    NewCircle->setOrigin(elmt.getRadius(), elmt.getRadius());
    NewCircle->setPosition(elmt.getCoord().x * scale/*- widthTex*/ , - elmt.getCoord().y * scale/* - heightTex*/);
    return NewCircle;
}

EditorObject* GravityCircle::clone() const
{
    return new GravityCircle(*this);
}

GravityCircle::~GravityCircle()
{
    //dtor
}
