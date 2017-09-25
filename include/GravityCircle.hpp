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

#ifndef GRAVITYCIRCLE_H
#define GRAVITYCIRCLE_H

#include <SFML/Graphics.hpp>
#include <list>

#include "../files.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "EditorCircle.hpp"


class GravityCircle : public EditorCircle
{
public:
    GravityCircle(float radius = 1.0f,float radiusMax=0.0f, bool defOrigin = true, std::string filename = FilenameNormalPointTex);
    GravityCircle(const GravityCircle& original);
    virtual ~GravityCircle();
    void grow(float step = 0.1f);
    virtual EditorObject* clone() const;
    virtual std::string save(float scale = GraphScale) const;
    virtual EditorObject* loadView(const Element& elmt, float scale);
//        std::list<> gravityCirclesList;
protected:
    std::string m_filename;
    float m_radiusMax;
    sf::Texture& m_texture;
};

#endif // GRAVITYCIRCLE_H
