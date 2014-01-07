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
        enum MoveType{/*ConstantSpeed, NaturalPhysic,*/ NoSliding, WithSliding};
        CharacterModel(bool life = true , sf::Vector2f coord = sf::Vector2f(0.0f, 0.0f), float speed = 6.0f, MoveType moveType = NoSliding);
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
/**/	{
/**/		return m_speed;
/**/	}
/**/
/**/	inline void CharacterModel::setCoords(const sf::Vector2f& coords)
/**/	{
/**/		m_PhysicsBox.setPosition(coords);
/**/	}
/**/
/**/	inline void CharacterModel::setCoords(float x, float y)
/**/	{
/**/		m_PhysicsBox.setPosition(sf::Vector2f(x,y));
/**/	}
/**/
/**/	inline void CharacterModel::setCoordX(float x)
/**/	{
/**/		m_PhysicsBox.setPosition(sf::Vector2f(x,m_PhysicsBox.getPosition().y));
/**/	}
/**/
/**/	inline void CharacterModel::setCoordY(float y)
/**/	{
/**/		m_PhysicsBox.setPosition(sf::Vector2f(m_PhysicsBox.getPosition().x,y));
/**/	}
/**/
/**/    inline void CharacterModel::setMoveType(MoveType moveType)
/**/	{
/**/		m_moveType = moveType;
/**/	}
/**/
/**/    inline void CharacterModel::setFrictionCoefficient(float frictionCoefficient)
/**/	{
/**/		m_frictionCoefficient = frictionCoefficient;
/**/	}

        inline float CharacterModel::getAngle() const {return m_PhysicsBox.getAngle();}

        inline void CharacterModel::setAngle(float angle)
        {
            angle = fmod(angle,360.0f);
            if(angle < 0 )
                angle += 360;
            m_PhysicsBox.setAngle(angle);
        }
/**/
/***************************************** // Definitions *****************************************/

#endif // CHARACTERMODEL_H
