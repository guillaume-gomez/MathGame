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

#ifndef PhysicsObject_HPP
#define PhysicsObject_HPP

#include "VisitorObjectCollidable.h"
#include "../constants.hpp"

#include <cmath>
#include <list>
#include <SFML/System/Vector2.hpp>

#ifdef DEBUG
#include <iostream>
#endif

namespace Physics
{
//it is implemented lower in this file
class Box;
class Circle;
class VisitorObjectCollidable;

class Object
{
    friend class Engine;

public:
    enum Type {Type_Box, Type_Circle};
    Object(Type type);
    virtual ~Object() = 0;
    Object(const Object& original);

    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f Position);

    sf::Vector2f getVelocity() const;
    void setVelocity(sf::Vector2f Velocity);

    sf::Vector2f getThrust() const;
    void setThrust(sf::Vector2f Thrust);

    float getAngle() const;
    void setAngle(float angle);

    bool isOnCurve() const;
    void isOnCurve(bool isIt);

    void jump(bool isJumping=true);
    bool isJumping() const;


    void setAllToNull();

    bool collidable() const;
    void collidable(bool isCollidable);

    //
    virtual bool testCollision(const Object& obj) const = 0;
    virtual bool testCollision(const Box& obj) const = 0;
    virtual bool testCollision(const Circle& obj) const = 0;

private:
    Object();
    Type m_type;
    sf::Vector2f m_Position;
    sf::Vector2f m_Velocity;

    sf::Vector2f m_Thrust;
    float m_angle;

    bool m_inEngine;
    bool m_onCurve;
    bool m_jumping;

    bool m_isCollidable;

    static std::list<Object*> m_CollidableObjects;
};

inline sf::Vector2f Object::getPosition() const
{
//        #ifdef DEBUG
//            // std::cout << m_Thrust.x << std::endl;
//        #endif
    return m_Position;
}

inline void Object::setPosition(sf::Vector2f Position)
{
    m_Position=Position;
}

inline sf::Vector2f Object::getVelocity() const
{
    return m_Velocity;
}
inline void Object::setVelocity(sf::Vector2f Velocity)
{
    m_Velocity=Velocity;
}

inline sf::Vector2f Object::getThrust() const
{
    return m_Thrust;
}
inline void Object::setThrust(sf::Vector2f Thrust)
{
    m_Thrust=Thrust;
}

inline float Object::getAngle() const
{
    return m_angle;
}
inline void Object::setAngle(float angle)
{
    m_angle = angle;
}

inline void Object::isOnCurve(bool onCurve)
{
    m_onCurve=onCurve;
}
inline bool Object::isOnCurve() const
{
    return m_onCurve;
}

inline bool Object::isJumping() const
{
    return m_jumping;
}


class Box : public Object
{
    friend class Engine;

public:
    Box(float width = 1.0f, float height = 1.0f);
    ~Box();
    Box(const Box& original);

    float getWidth() const;
    float getHeight() const;
    void setSize(float width, float height);

//            void setAllToNull();

    static VisitBox visitor;

    virtual bool testCollision(const Object& obj) const;
    virtual bool testCollision(const Box& obj) const;
    virtual bool testCollision(const Circle& obj) const;

private:
//            Box();
    float m_width, m_height;
};

inline float Box::getWidth() const
{
    return m_width;
}
inline float Box::getHeight() const
{
    return m_height;
}

class Circle : public Object
{
    friend class Engine;

public:
    Circle(float radius = 1.0f);
    ~Circle();
    Circle(const Circle& original);

    float getWidth() const;
    float getHeight() const;

    float getRadius() const;
    void setRadius(float radius);

//            void setAllToNull();

//            static VisitCircle visitor;

    void setAsGravityCircle();

    virtual bool testCollision(const Object& obj) const;
    virtual bool testCollision(const Box& obj) const;
    virtual bool testCollision(const Circle& obj) const;

private:
//            Box();
    float m_radius;
    static std::list<Circle*> m_gravityCircles;
    bool m_isGravityCircle;
};

inline float Circle::getWidth() const
{
    return m_radius*2;
}
inline float Circle::getHeight() const
{
    return m_radius*2;
}

inline float Circle::getRadius() const
{
    return m_radius;
}
inline void Circle::setRadius(float radius)
{
    m_radius=radius/GraphScale ;
}
} // namespace Physics

#endif // PhysicsObject_HPP
