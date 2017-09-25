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

#include "ObjectFactoryAbstract.hpp"
#include "../constants.hpp"
#include "GravityCircle.hpp"
#include "Point.hpp"

#include <stdexcept>


ObjectFactoryAbstract::ObjectFactoryAbstract()
{}

ObjectFactoryAbstract::~ObjectFactoryAbstract()
{
    //dtor
}

std::map<TypeObject, EditorObject*> ObjectFactoryAbstract::m_map = std::map<TypeObject, EditorObject*>();

void ObjectFactoryAbstract::_register (const TypeObject key, EditorObject* obj)
{
    if(m_map.find(key) == m_map.end())
    {
        m_map[key] = obj;
    }
}

EditorObject* ObjectFactoryAbstract::create(const TypeObject& key)
{
    EditorObject* newObject = nullptr;
    std::map<TypeObject, EditorObject*>::const_iterator it = m_map.find(key);

    if(m_map.size() == 0)
    {
        std::runtime_error("In the ObjectFactoryAbstract::create : the factory hasn't got any template method");
    }

    if(it != m_map.end())
    {
        newObject = ((*it).second)->clone();
    }
    else
    {
        std::runtime_error("In the ObjectFactoryAbstract::create : cannot make an object like this");
    }

    return newObject;
}
