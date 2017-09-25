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

#ifndef EditorCircle_H
#define EditorCircle_H

#include "PhysicsEngine.hpp"

#include <SFML/Graphics.hpp>

#include "EditorObject.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


//std::string toString(TypeObject const& type) const;

/**
@brief : a wrapper class to manage different kind of object circleShape
**/

class EditorCircle : public sf::CircleShape , public EditorObject
{
public:
    EditorCircle();
    EditorCircle(const EditorCircle& original);
    virtual ~EditorCircle();
    virtual float distance(sf::Vector2f pointOne, sf::Vector2f pointTwo);
    virtual bool isCollide(sf::Vector2f point);
    virtual bool isCollide(const sf::FloatRect& rect);
    virtual void draw(sf::RenderTarget& app);
    virtual EditorObject* clone() const = 0;
//    	virtual void setPosition(float x, float y);
//        virtual void setPosition(sf::Vector2f& pos);
    virtual void setPosition(float x, float y);
    virtual void setPosition(sf::Vector2f& pos);
    virtual sf::Vector2f get_Position() const ;
    virtual sf::FloatRect get_GlobalBounds() const;
    virtual std::string save(float scale = GraphScale) const;
    virtual EditorObject* loadView(const Element& elmt, float scale) = 0;

    void setRadius(float radius);
    const Physics::Circle& getPhysicsCircle() const;

protected:
    Physics::Circle m_physicsCircle;

};

//inline void EditorCircle::setPosition(float x, float y)
//{
//    CircleShape::setPosition(x,y);
//}

//inline void EditorCircle::setPosition(sf::Vector2f& pos)
//{
//    setPosition(pos.x, pos.y);
//}

inline void EditorCircle::setPosition(float x, float y)
{
    CircleShape::setPosition(x,y);
    m_physicsCircle.setPosition(sf::Vector2f(x/GraphScale, -y/GraphScale));
}

inline void EditorCircle::setPosition(sf::Vector2f& pos)
{
    setPosition(pos.x, pos.y);
}

inline sf::Vector2f EditorCircle::get_Position() const
{
//    #ifdef DEBUG
//        std::cout << "get_Position x : " << getPosition().x << " , y : " << getPosition().y << std::endl;
//    #endif
    return this->getPosition();
}

inline  sf::FloatRect EditorCircle::get_GlobalBounds() const
{
//    #ifdef DEBUG
//        std::cout << "getGlobalBounds x : " << getGlobalBounds().left << " , y : " << getGlobalBounds().top << std::endl;
//    #endif
//    return m_physicsCircle.getPosition();
    return this->getGlobalBounds();
}

inline const Physics::Circle& EditorCircle::getPhysicsCircle() const
{
    return m_physicsCircle;
}


#endif // EditorCircle_H
