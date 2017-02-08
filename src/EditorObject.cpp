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

#include "EditorObject.hpp"

const std::map<TypeObject,std::string> EditorObject::objectStrMap =
{
    {TypeObject::Hero, HeroStr},
    {TypeObject::Abstract, AbstractStr},
    {TypeObject::Point, PointStr},
    {TypeObject::GoalPoint, GoalPointStr},
    {TypeObject::Circle, CircleStr},
    {TypeObject::Enemy, EnemyStr},
    {TypeObject::Integral, IntegralStr},
    {TypeObject::Function, FunctionStr},
    {TypeObject::Info, InfoStr}
};

const std::map<TypeObject,int> EditorObject::objectValueMap =
{
    {TypeObject::Hero, -1},
    {TypeObject::Abstract, -1},
    {TypeObject::Point, 4},
    {TypeObject::GoalPoint, 5},
    {TypeObject::Enemy, 3},
    {TypeObject::Circle, 2},
    {TypeObject::Integral,1},
    {TypeObject::Function,1},
    {TypeObject::Info, 0}
};


EditorObject::EditorObject()
{

}

EditorObject::~EditorObject()
{
    //dtor
}

TypeObject EditorObject::getTypeByStr(const std::string str)
{
    for (auto it : EditorObject::objectStrMap)
    {
        if(it.second == str)
        {
            return it.first;
        }
    }
    std::runtime_error("EditorObject::getTypeByStr(const std::string str)  cannot find this value");
    return TypeObject::Abstract;
}

std::string EditorObject::getTypeStr() const
{
    return getTypeStr(m_type);
}

std::string EditorObject::getTypeStr(const TypeObject& type)
{
    const std::map<TypeObject,std::string>::const_iterator it =  EditorObject::objectStrMap.find(type);
    if(it != objectStrMap.end())
    {
        return it->second;
    }
    else
    {
        return AbstractStr;
    }
}


bool EditorObject::compare(const EditorObject* r1, const EditorObject* r2)
{
    return EditorObject::objectValueMap.at(r1->getType()) < EditorObject::objectValueMap.at(r2->getType());
}
