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

#include "PhysicsObject.hpp"

using namespace Physics;

std::list<Object*> Object::m_CollidableObjects;

Object::Object()
{}

Object::Object(Type type)
    :m_type(type), m_Position(sf::Vector2f(0.0f,0.0f)), m_Velocity(sf::Vector2f(0.0f,0.0f)), m_inEngine(false), m_onCurve(false), m_jumping(false), m_isCollidable(false)
{}

Object::~Object()
{
    if(m_isCollidable)
    {
        m_isCollidable = false;
        m_CollidableObjects.remove(this);
    }
//    #ifdef DEBUG
//         std::cout << "destructeur Object::Object" << std::endl;
//    #endif
}

Object::Object(const Object& original)
    :m_type(original.m_type), m_Position(original.m_Position), m_Velocity(original.m_Velocity), m_Thrust(original.m_Thrust)
    ,m_angle(original.m_angle), m_inEngine(original.m_inEngine), m_onCurve(original.m_onCurve), m_jumping(original.m_jumping)
{
//    #ifdef DEBUG
//        // std::cout << "constructeur de copie Object::Object" << std::endl;
//    #endif
}

void Object::jump(bool isJumping)
{
//    if(m_onCurve)
    m_jumping=isJumping;
}

void Object::setAllToNull()
{
    m_Position = sf::Vector2f(0.0f,0.0f);
    m_Velocity = sf::Vector2f(0.0f,0.0f);

    m_Thrust = sf::Vector2f(0.0f,0.0f);
    m_angle = 0.0f;
    jump(false);
}

bool Object::collidable() const
{
    return m_isCollidable;
}

void Object::collidable(bool isCollidable)
{
    if(!m_isCollidable && isCollidable)
    {
        m_isCollidable = true;
        m_CollidableObjects.push_back(this);
    }
    else if(m_isCollidable && !isCollidable)
    {
        m_isCollidable = false;
        m_CollidableObjects.remove(this);
    }
}

/***************************************************************/
/************************** Class Box **************************/
/**************************           **************************/

VisitBox Box::visitor;

Box::Box(float width, float height)
    :Object(Object::Type_Box)
{
    setSize(width, height);
}

Box::~Box()
{
}

Box::Box(const Box& original)
    :Object(original), m_width(original.m_width), m_height(original.m_height)
{
//    #ifdef DEBUG
//        // std::cout << "constructeur de copie Box::Box" << std::endl;
//    #endif
}

//void Box::setAllToNull()
//{
//    Object::setAllToNull();
//}

bool Box::testCollision(const Object& obj) const
{
    // bool truc = visitor.visit(*this, obj);
//   switch()
    const Box* box = dynamic_cast<const Box*>(&obj);
    return testCollision(*box);
    // std::cout << "Box::testCollision with PhysicObject" << truc << std::endl;
}

bool Box::testCollision(const Box& obj) const
{
    return Box::visitor.visit(*this, obj);
}

bool Box::testCollision(const Circle& obj) const
{
    return Box::visitor.visit(*this, obj);
}

void Box::setSize(float width, float height)
{
//    #ifdef DEBUG
//        std::cout << "width : " << width << std::endl;
//        std::cout << "height : " << height << std::endl;
//    #endif // DEBUG
    if(width<0.0)
        width*=-1;
    if(height<0.0)
        height*=-1;

    m_width=width/GraphScale;
    m_height=height/GraphScale ;
}

//
//bool Box::testCollision(const Circle& obj) const
//{
//    return Box::visitor.visit(*this, obj);
//}

/******************************************************************/
/************************** Class Circle **************************/
/**************************              **************************/

std::list<Circle*> Circle::m_gravityCircles;

//VisitCircle Circle::visitor;

Circle::Circle(float radius)
    :Object(Object::Type_Circle), m_radius(radius), m_isGravityCircle(false)
{
    if(m_radius<0.0)
        m_radius*=-1;
}

Circle::~Circle()
{
    if(m_isGravityCircle)
    {
        m_gravityCircles.remove(this);
    }
}

Circle::Circle(const Circle& original)
    :Object(original), m_radius(original.m_radius), m_isGravityCircle(original.m_isGravityCircle)
{

}

void Circle::setAsGravityCircle()
{
    if(!m_isGravityCircle)
    {
        m_isGravityCircle = true;
        m_gravityCircles.push_back(this);
    }
}

bool Circle::testCollision(const Object& obj) const
{
    return false;
}
bool Circle::testCollision(const Box& obj) const
{
    return false;
}
bool Circle::testCollision(const Circle& obj) const
{
    return false;
}
