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

#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include <string>

#include <SFML/Graphics.hpp>

#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "Element.hpp"

/**
@brief : a wrapper class to manage different kind of object
**/

class EditorObject
{
public:
    EditorObject();
    virtual ~EditorObject();
    virtual void draw(sf::RenderTarget& app) = 0;
    inline virtual TypeObject getType() const
    {
        return m_type;
    }
    std::string getTypeStr() const ;
    static std::string getTypeStr(const TypeObject& type);
    static bool compare(const EditorObject* r1, const EditorObject* r2);
    static TypeObject getTypeByStr(const std::string str);
    virtual EditorObject* clone() const = 0;
//        virtual void setPosition(sf::Vector2f& position) = 0;
//        virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(sf::Vector2f& pos) = 0;
    virtual sf::FloatRect get_GlobalBounds() const = 0;
    virtual sf::Vector2f get_Position() const = 0;
    virtual std::string save(float scale = GraphScale) const = 0;
    virtual EditorObject* loadView(const Element& elmt, float scale) = 0;

protected:
    static const std::map<TypeObject,std::string> objectStrMap;
    static const std::map<TypeObject, int> objectValueMap;
    TypeObject m_type;
private:
};

#endif // EDITOROBJECT_H
