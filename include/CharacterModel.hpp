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

#ifndef CHARACTERMODEL_H
#define CHARACTERMODEL_H

#include "ConstrueFunction.hpp"
#include "../constants.hpp"
#include "PhysicsEngine.hpp"
#include "../libs/TextAreaSFML2_0.hpp"

#include <SFML/Graphics.hpp>

#include <cmath>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

class CharacterModel
{
public:
    enum MoveType {/*ConstantSpeed, NaturalPhysic,*/ NoSliding, WithSliding};
    CharacterModel(bool life = true , sf::Vector2f coord = sf::Vector2f(0.0f, 0.0f), float speed = 6.0f, MoveType moveType = NoSliding);
    CharacterModel(const CharacterModel& copy);
    bool isAlive() const;
    const sf::Vector2f getCoords() const;
    const sf::Vector2f getVelocity() const;
    void setLife(bool _life);
    float getSpeed() const;
    void setCoords(const sf::Vector2f& coords);
    void setCoords(float x, float y);
    void setCoordX(float x);
    void setCoordY(float y);
    void setWidth(int _w);
    void setHeight(int _h);
    void setSize(int _w, int _h);
    sf::FloatRect getRect() const;
    sf::FloatRect getRectScaled(float graphScale)const;
    virtual void handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
    virtual ~CharacterModel();
    void setMoveType(MoveType moveType);
    void setFrictionCoefficient(float frictionCoefficient);
    float getAngle() const;
    void setAngle(float angle);
    void checkisAlive();
    void setDirection(bool dir);
    bool getDirection() const;
    const Physics::Box& getPhysicsBox() const;
    void addToEngine();

protected:
    Physics::Box m_PhysicsBox;
    bool m_life;
    float m_frictionCoefficient;
    float m_speed;
    MoveType m_moveType;
    bool m_orientedRight;
    int m_height;
    int m_width;
};

/***************************************** Definitions *****************************************/
/**/
///**/    inline void CharacterModel::setSpeed(float speed)
///**/	{
///**/		m_speed=speed;
///**/	}
/**/
/**/    inline float CharacterModel::getSpeed() const
/**/
{
    /**/		return m_speed;
    /**/
}
/**/
/**/	inline void CharacterModel::setCoords(const sf::Vector2f& coords)
/**/
{
    /**/		m_PhysicsBox.setPosition(coords);
    /**/
}
/**/
/**/	inline void CharacterModel::setCoords(float x, float y)
/**/
{
    /**/		m_PhysicsBox.setPosition(sf::Vector2f(x,y));
    /**/
}
/**/
/**/	inline void CharacterModel::setCoordX(float x)
/**/
{
    /**/		m_PhysicsBox.setPosition(sf::Vector2f(x,m_PhysicsBox.getPosition().y));
    /**/
}
/**/
/**/	inline void CharacterModel::setCoordY(float y)
/**/
{
    /**/		m_PhysicsBox.setPosition(sf::Vector2f(m_PhysicsBox.getPosition().x,y));
    /**/
}
/**/
/**/    inline void CharacterModel::setMoveType(MoveType moveType)
/**/
{
    /**/		m_moveType = moveType;
    /**/
}
/**/
/**/    inline void CharacterModel::setFrictionCoefficient(float frictionCoefficient)
/**/
{
    /**/		m_frictionCoefficient = frictionCoefficient;
    /**/
}

inline float CharacterModel::getAngle() const
{
    return m_PhysicsBox.getAngle();
}

inline void CharacterModel::setAngle(float angle)
{
    angle = fmod(angle,360.0f);
    if(angle < 0 )
        angle += 360;
    m_PhysicsBox.setAngle(angle);
}

inline const Physics::Box& CharacterModel::getPhysicsBox() const
{
//            #ifdef DEBUG
//                // std::cout << "CharacterModel::getPhysicsBox() : debugText : " << debugText << std::endl;
//            #endif
    return m_PhysicsBox;
}

inline void CharacterModel::addToEngine()
{
    m_PhysicsBox.collidable(true);
}
/**/
/***************************************** // Definitions *****************************************/

#endif // CHARACTERMODEL_H
