#ifndef CHARACTERMODEL_H
#define CHARACTERMODEL_H

#include <cmath>
#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#include <SFML/Graphics.hpp>

#include "ConstrueFunction.hpp"
#include "../constants.hpp"
#include "../libs/TextAreaSFML2_0.hpp"

class CharacterModel
{
    public:
        enum MoveType{/*ConstantSpeed, NaturalPhysic,*/ NoSliding, WithSliding};
        CharacterModel(bool life = true , sf::Vector2f coord = sf::Vector2f(0.0f, 0.0f), float speed = 6.0f, MoveType moveType = NoSliding);
        bool getLife() const;
        const sf::Vector2f& getCoords() const;
        const sf::Vector2f& getVelocity() const;
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
        void handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
        void resetTimer();
        void move(ConstrueFonction& _function);
        virtual ~CharacterModel();
        void resetVelocity();
        void setMoveType(MoveType moveType);
		void setFrictionCoefficient(float frictionCoefficient);
		float getAngle()const {return m_angle;};
		void setAngle(float angle){m_angle = angle;};

    private:
        bool m_life;
        sf::Vector2f m_velocity;
        sf::Vector2f m_thrust;
        sf::Vector2f m_coords;
        float m_speed;
        float m_frictionCoefficient;
        float m_actualSpeed;
        MoveType m_moveType;
        float m_angle;

        bool m_orientedRight;
        int m_height;
        sf::Clock m_timer;
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
/**/		m_coords = coords;
/**/	}
/**/
/**/	inline void CharacterModel::setCoords(float x, float y)
/**/	{
/**/		m_coords.x = x;
/**/		m_coords.y = y;
/**/	}
/**/
/**/	inline void CharacterModel::setCoordX(float x)
/**/	{
/**/		m_coords.x = x;
/**/	}
/**/
/**/	inline void CharacterModel::setCoordY(float y)
/**/	{
/**/		m_coords.y = y;
/**/	}
/**/
/**/	inline void CharacterModel::resetTimer()
/**/	{
/**/		m_timer.restart();
/**/	}
/**/
/**/	inline void CharacterModel::resetVelocity()
/**/	{
/**/		m_velocity.x = 0.0f;
/**/		m_velocity.y = 0.0f;
/**/		m_actualSpeed = 0.0f;
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
/**/
/***************************************** // Definitions *****************************************/

#endif // CHARACTERMODEL_H
