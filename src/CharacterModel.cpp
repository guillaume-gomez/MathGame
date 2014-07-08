#include "CharacterModel.hpp"
#include <iostream>

/**
* @brief : Constructor
* @param : life of the character
* @param : Initial position of the character
**/
CharacterModel::CharacterModel(bool life  , sf::Vector2f coord, float speed, MoveType moveType)
:m_life(life), m_frictionCoefficient(0.0f), m_speed(speed), m_moveType(moveType)
{
    #ifdef DEBUG
//        std::cout << "CharacterModel constructor : &m_PhysicsBox : " << &m_PhysicsBox << std::endl;
    #endif // DEBUG
	m_orientedRight = (m_PhysicsBox.getVelocity().x>0);
	Physics::Engine::getEngine()->addObject(&m_PhysicsBox);
}


CharacterModel::CharacterModel(const CharacterModel& copy)
:m_life(copy.m_life), m_frictionCoefficient(copy.m_frictionCoefficient), m_speed(copy.m_speed), m_moveType(copy.m_moveType)
{
    #ifdef DEBUG
//        std::cout << " copy constryctor CharacterModel" << std::endl;
    #endif // DEBUG
  m_orientedRight = (m_PhysicsBox.getVelocity().x>0);
  Physics::Engine::getEngine()->addObject(&m_PhysicsBox);
}

void CharacterModel::setDirection(bool dir)
{
std::cout << "CharacterModel::orientedRight " << dir << std::endl;
  m_orientedRight = dir;
}

bool CharacterModel::getDirection() const
{
  return m_orientedRight;
}

/**
* @brief : Accessor of life
**/
bool CharacterModel::isAlive() const
{return m_life;}


void CharacterModel::checkisAlive()
{
    if(this->getCoords().y > sentinelY)
    {
        m_life = false;
    }

    if(this->getCoords().x > sentinelX)
    {
        m_life = false;
    }
}
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
const sf::Vector2f CharacterModel::getCoords() const
{
    return m_PhysicsBox.getPosition();
}

/**
* @brief : Accessor of velocity
**/
const sf::Vector2f CharacterModel::getVelocity() const
{return m_PhysicsBox.getVelocity();}


 void CharacterModel::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
 {
    if(event.type == sf::Event::KeyPressed)
     {
        switch(event.key.code)
        {
        case sf::Keyboard::Up:
            if(!m_PhysicsBox.isJumping())
                m_PhysicsBox.jump();
            break;

//        case sf::Keyboard::Down:
//         m_thrust.y = +m_speed;
//          break;

        case sf::Keyboard::Left:
            m_PhysicsBox.setThrust(sf::Vector2f(-m_speed, m_PhysicsBox.getThrust().y));
            break;

        case sf::Keyboard::Right:
            m_PhysicsBox.setThrust(sf::Vector2f(m_speed, m_PhysicsBox.getThrust().y));
             #ifdef DEBUG
          //     // std::cout << "characterModel this : " << this << " thrust : " << m_PhysicsBox.getThrust().x << std::endl;
            //    // std::cout << "charracterModel getPhysicsBox().getThrust() : " << getPhysicsBox("xthrust").getThrust().x << std::endl;
            #endif
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
                 m_PhysicsBox.setThrust(sf::Vector2f(0.0f, m_PhysicsBox.getThrust().y));
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
        m_PhysicsBox.setThrust(sf::Vector2f(0.0f, m_PhysicsBox.getThrust().y));
    }
 }


void CharacterModel::setWidth(int _w)
{
    setSize(_w, m_height);
}

void CharacterModel::setHeight(int _h)
{
    setSize(m_width, _h);
}

void CharacterModel::setSize(int _w, int _h)
{
    m_width = _w;
    m_height = _h;
    m_PhysicsBox.setSize(m_width, m_height);
}

sf::FloatRect CharacterModel::getRect() const
{
    return sf::FloatRect(m_PhysicsBox.getPosition().x , m_PhysicsBox.getPosition().y, (float) m_width, (float)m_height);
}

sf::FloatRect CharacterModel::getRectScaled(float graphScale)const
{
    return sf::FloatRect(m_PhysicsBox.getPosition().x  , m_PhysicsBox.getPosition().y , (float) m_width / graphScale , (float)m_height / graphScale);
}

/**
* @brief : Destructor of the class
**/
CharacterModel::~CharacterModel()
{
    #ifdef DEBUG
//        std::cout << "destructor CharacterModel" << std::endl;
    #endif // DEBUG
	Physics::Engine::getEngine()->delObject(&m_PhysicsBox);
}
