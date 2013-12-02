#include "CharacterModel.hpp"
#include <iostream>

/**
* @brief : Constructor
* @param : life of the character
* @param : Initial position of the character
**/
CharacterModel::CharacterModel(bool life  , sf::Vector2f coord, float speed, MoveType moveType)
:m_life(life), m_velocity(0.0f, 0.0f), m_thrust(0.0f, 0.0f), m_coords(coord), m_speed(speed), m_frictionCoefficient(0.0f), m_actualSpeed(sqrt(m_velocity.y * m_velocity.y + m_velocity.x * m_velocity.x)), m_moveType(moveType), m_angle(0.0f)
{
	m_orientedRight = (m_velocity.x>0);
}

/**
* @brief : Accessor of life
**/
bool CharacterModel::getLife() const
{return m_life;}

/**
* @brief : Accessor of life
**/
void CharacterModel::setLife(bool _life) {m_life = _life;}

//   void CharacterModel::setVelocityX(float x)
//   {
//       m_velocity.x = x;
//   }

//void CharacterModel::setVelocityY(float y)
//{
//    m_velocity.y = y ;
//}

//
///**
//* @brief : Accessor of velocity.x
//**/
//float CharacterModel::getVelX(){return m_thrust.x ;}
//
///**
//* @brief : Accessor of velocity.y
//**/
//float CharacterModel::getVelY(){return  m_thrust.y; }

/**
* @brief : Accessor of coord.x
**/
//float CharacterModel::getCoordX(){return m_coord.x;}
//
///**
//* @brief : Accessor of coord.y
//**/
//float CharacterModel::getCoordY(){return m_coord.y;}

/**
* @brief : Accessor of coord
**/
const sf::Vector2f& CharacterModel::getCoords() const
{return m_coords;}

/**
* @brief : Accessor of velocity
**/
const sf::Vector2f& CharacterModel::getVelocity() const
{return m_thrust;}



 void CharacterModel::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
 {
    if(event.type == sf::Event::KeyPressed)
     {
        switch(event.key.code)
     	{
//		case sf::Keyboard::Up:
//		    m_thrust.y = -m_speed;
//			break;

//        case sf::Keyboard::Down:
//		   m_thrust.y = +m_speed;
//			break;

        case sf::Keyboard::Left:
		    m_thrust.x = -m_speed;
			break;

        case sf::Keyboard::Right:
		   m_thrust.x = m_speed;
			break;

		default:
			break;
     	}
     }
     else if(event.type == sf::Event::KeyReleased)
     {
        if(/*!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            &&*/ !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
//            && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
             switch(event.key.code)
             {
//              case sf::Keyboard::Up:
//                m_thrust = sf::Vector2f(0.0f,0.0f);
//               break;
              case sf::Keyboard::Right:
              case sf::Keyboard::Left:
                 m_thrust.x=0.0f;
               break;
//              case sf::Keyboard::Down:
//               m_thrust = sf::Vector2f(0.0f,0.0f);
//               break;

             default:
              break;
             }
        }
    }
    if(textAreaFunction.getAlphaColor()==Clear)
    {
		m_thrust.x=0;
 	}
 }


void CharacterModel::move(ConstrueFonction& _function)
{
	static float yCurve, elapsedSeconds, derivative;
	//static float xprev;
	//static float yCurvePrev;
//	const int stepToCalculationAngle = 0.1;
	m_angle = 0.0f;

//	xprev = m_coords.x- stepToCalculationAngle;

	// si la courbe est représentée en ce point x
	if(_function.isRepresented(m_coords.x))
	{
		yCurve = _function.getFunctionValue(m_coords.x);
		//yCurvePrev = _function.getFunctionValue(xprev);

		switch(m_moveType)
		{
		case NoSliding:
			// si le personnage est au dessus de la courbe
			if(m_coords.y>yCurve)
			{
				elapsedSeconds = m_timer.getElapsedTime().asSeconds();
				m_velocity.y += GravityAcceleration.y*elapsedSeconds;

				m_coords += m_velocity*elapsedSeconds;
				// si le personnage a traversé la courbe on le positionne sur la courbe
				if(_function.isRepresented(m_coords.x))
				{
					if(m_coords.y < _function.getFunctionValue(m_coords.x))
						m_coords.y=_function.getFunctionValue(m_coords.x);
				}
			}
			// si le personnage est sur la courbe
			else if(m_coords.y == yCurve)
			{
				derivative=_function.getDerivative(m_coords.x);
				m_velocity.x=cos(atan2(derivative, (m_thrust.x<0 ? -1 : 1)))*abs(m_thrust.x);
				m_velocity.y=sin(atan2(derivative, (m_thrust.x<0 ? -1 : 1)))*m_thrust.x;

				m_coords += m_velocity*m_timer.getElapsedTime().asSeconds();
				// si apres déplacement le personnage est toujours dans une zone où la courbe est représentée
				if(_function.isRepresented(m_coords.x))
				{
					yCurve = _function.getFunctionValue(m_coords.x);
					// si le personnage est en dessous de la courbe (due aux erreurs inéluctables de précision de calcul)
					// alors correction en placant le personnage sur la bonne coordonnée y
					// si il est au dessus, on ne fait rien et au prochain appel de cette methode le perso sera déplacé en retombant selon la gravité
					if(m_coords.y < yCurve)
						m_coords.y = yCurve;
				}

			}
			// si le personnage est en dessous de la courbe
			else
			{
				elapsedSeconds = m_timer.getElapsedTime().asSeconds();
				m_velocity.y += GravityAcceleration.y*elapsedSeconds;
				m_coords += m_velocity*elapsedSeconds;
			}
			break;

		case WithSliding:
			if(m_coords.y>yCurve)
			{
				elapsedSeconds = m_timer.getElapsedTime().asSeconds();
				m_velocity.y += GravityAcceleration.y*elapsedSeconds;
				m_actualSpeed = sqrt(m_velocity.y*m_velocity.y + m_velocity.x*m_velocity.x);

				m_coords += m_velocity*elapsedSeconds;
				// si le personnage a traversé la courbe on le positionne sur la courbe
				if(_function.isRepresented(m_coords.x))
				{
					if(m_coords.y < _function.getFunctionValue(m_coords.x))
					{
						m_coords.y=_function.getFunctionValue(m_coords.x);
						m_actualSpeed-=fabs(sin(atan(derivative))*m_velocity.y*elapsedSeconds);
						m_actualSpeed-=fabs(cos(atan(derivative))*m_velocity.x*elapsedSeconds);
						derivative = _function.getDerivative(m_coords.x);
						if(m_orientedRight)
						{
							m_velocity.x = cos(atan(derivative))*m_actualSpeed;			// toujours positif CSDSFFSQFS
							m_velocity.y = sin(atan(derivative))*m_actualSpeed;
						}
						else
						{
							m_velocity.x = -cos(atan(derivative))*m_actualSpeed;			// toujours positif CSDSFFSQFS
							m_velocity.y = -sin(atan(derivative))*m_actualSpeed;
						}
					}

				}
			}
			// si le personnage est sur la courbe
			else if(m_coords.y == yCurve)
			{
				elapsedSeconds = m_timer.getElapsedTime().asSeconds();
				derivative = _function.getDerivative(m_coords.x);

				if(m_velocity.y > 0)
					m_actualSpeed -= fabs(sin(atan(derivative)) * GravityAcceleration.y * elapsedSeconds);
				else
					m_actualSpeed += fabs(sin(atan(derivative)) * GravityAcceleration.y * elapsedSeconds);

				if((m_velocity.x > 0 && m_thrust.x > 0) || (m_velocity.x < 0 && m_thrust.x < 0))
					m_actualSpeed += fabs(cos(atan(derivative)) * m_thrust.x * elapsedSeconds * 3);
				else
					m_actualSpeed -= fabs(cos(atan(derivative)) * m_thrust.x * elapsedSeconds * 3);

				if(m_actualSpeed < 0)
				{
					m_orientedRight = !m_orientedRight;
					m_actualSpeed *= -1;
				}

				float friction = m_actualSpeed * m_actualSpeed * m_frictionCoefficient;
				m_actualSpeed -= friction * elapsedSeconds;

				if(m_orientedRight)
				{
					m_velocity.x = cos(atan(derivative)) * m_actualSpeed;			// toujours positif CSDSFFSQFS
					m_velocity.y = sin(atan(derivative)) * m_actualSpeed;
				}
				else
				{
					m_velocity.x = -cos(atan(derivative)) * m_actualSpeed;			// toujours positif CSDSFFSQFS
					m_velocity.y = -sin(atan(derivative)) * m_actualSpeed;
				}
//				m_velocity.x = cos(atan(derivative))*m_actualSpeed;			// toujours positif CSDSFFSQFS
//				m_velocity.y = sin(atan(derivative))*m_actualSpeed;
				m_coords += m_velocity * m_timer.getElapsedTime().asSeconds();
				// si apres déplacement le personnage est toujours dans une zone où la courbe est représentée
				if(_function.isRepresented(m_coords.x))
				{
					yCurve = _function.getFunctionValue(m_coords.x);
					// si le personnage est en dessous de la courbe (due aux erreurs inéluctables de précision de calcul)
					// alors correction en placant le personnage sur la bonne coordonnée y
					// si il est au dessus, on ne fait rien et au prochain appel de cette methode le perso sera déplacé en retombant selon la gravité
					if(m_coords.y < yCurve)
					{
					//	m_velocity.y += yCurve-m_coords.y;
						m_coords.y = yCurve;
					}
				}
			}
			else
			{
				elapsedSeconds = m_timer.getElapsedTime().asSeconds();
				m_velocity.y += GravityAcceleration.y * elapsedSeconds;
				m_actualSpeed = sqrt(m_velocity.y * m_velocity.y + m_velocity.x * m_velocity.x);
				m_coords += m_velocity * elapsedSeconds;
			}
			break;

		default:
			break;
		}

     m_angle = atan(derivative);

	}
	// si la courbe n'est pas représenté en ce x (i.e : c'est le videeeeeeeeeeee!)
	else
	{
		m_velocity.y += GravityAcceleration.y * m_timer.getElapsedTime().asSeconds();
		m_coords += m_velocity * m_timer.getElapsedTime().asSeconds();
	}
	m_timer.restart();
}


void CharacterModel::setWidth(int _w)
{
    m_width = _w;
}

void CharacterModel::setHeight(int _h)
{
    m_height = _h;
}

void CharacterModel::setSize(int _w, int _h)
{
   m_width = _w;
   m_height = _h;
}

sf::FloatRect CharacterModel::getRect() const
{
    return sf::FloatRect(m_coords.x , m_coords.y, (float) m_width, (float)m_height);
}


/**
* @brief : Destructor of the class
**/
CharacterModel::~CharacterModel()
{
    //dtor
}
