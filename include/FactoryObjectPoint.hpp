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

#ifndef FACTORYOBJECTPOINT_HPP
#define FACTORYOBJECTPOINT_HPP

#include "../constants.hpp"
#include "../files.hpp"
#include "ObjectFactoryAbstract.hpp"
#include "Point.hpp"

class FactoryObjectPoint : public ObjectFactoryAbstract
{
public:
    FactoryObjectPoint();
    virtual ~FactoryObjectPoint();
    virtual EditorObject* setTypeObject (std::string type);
protected:
private:
};
#endif // FACTORYOBJECTPOINT_HPP

