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

#include "VisitorObjectCollidable.h"
#include "PhysicsObject.hpp"

#include <iostream>

using namespace  Physics;

VisitorObjectCollidable::VisitorObjectCollidable()
{}

VisitorObjectCollidable::~VisitorObjectCollidable()
{}

bool VisitBox::visit(const Box& box1, const Box& box2)
{
//    #ifdef DEBUG
//        std::cout << "box1.width : " << box1.getWidth() << " box2.width : " << box2.getWidth() << std::endl;
//        std::cout << "box1.x : " << box1.getPosition().x << " box2.x : " << box2.getPosition().x << std::endl;
//    #endif // DEBUG
    return !((box2.getPosition().x >= box1.getPosition().x + box1.getWidth()/2)  // trop à droite
             || (box2.getPosition().x + box2.getWidth()/2 <= box1.getPosition().x)  // trop à gauche
             || (box2.getPosition().y >= box1.getPosition().y + box2.getHeight()/2) // trop en bas
             || (box2.getPosition().y + box2.getHeight()/2 <= box1.getPosition().y)) // trop en haut
           ;
}

bool VisitBox::visit(const Box& box, const Circle& circle)
{
//    #ifdef DEBUG
//        std::cout << "box : "     << "x : " << box.getPosition().x    << " y : " << box.getPosition().y << std::endl;
//        std::cout << "circle : "  << "x : " << circle.getPosition().x << " y : " << circle.getPosition().y << std::endl << std::endl;
//    #endif // DEBUG

    float x,y;
    float boxCenterY = box.getPosition().y+box.getHeight()/2;

    if(box.getPosition().x > circle.getPosition().x)
        x = box.getPosition().x-circle.getPosition().x;
    else
        x = circle.getPosition().x-box.getPosition().x;

    if(boxCenterY > circle.getPosition().y)
        y = boxCenterY-circle.getPosition().y;
    else
        y = circle.getPosition().y-boxCenterY;

    return (sqrt(x*x+y*y) <= (box.getWidth()/2 + circle.getRadius()) );
}
