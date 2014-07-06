#include "PhysicsObject.hpp"

using namespace Physics;

std::list<Object*> Object::m_CollidableObjects;

Object::Object()
:m_Position(sf::Vector2f(0.0f,0.0f)), m_Velocity(sf::Vector2f(0.0f,0.0f)), m_inEngine(false), m_onCurve(false), m_jumping(false), m_isCollidable(false)
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
:m_Position(original.m_Position), m_Velocity(original.m_Velocity), m_Thrust(original.m_Thrust)
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


Box::Box(float width, float height)
:m_width(width), m_height(height)
{
    if(m_width<0.0)
        m_width*=-1;
    if(m_height<0.0)
        m_height*=-1;
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

void Box::setAllToNull()
{
    Object::setAllToNull();
}

bool Box::testCollision(VisitorObjectCollidable& visitor, const Object& obj) const
{
   // bool truc = visitor.visit(*this, obj);
   const Box* box = dynamic_cast<const Box*>(&obj);
   return testCollision(visitor, *box);
   // std::cout << "Box::testCollision with PhysicObject" << truc << std::endl;
}


bool Box::testCollision(VisitorObjectCollidable& visitor, const Box& obj) const
{
    return visitor.visit(*this, obj);
}
