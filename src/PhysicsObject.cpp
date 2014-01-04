#include "PhysicsObject.hpp"

using namespace Physics;

Object::Object()
:m_Position(sf::Vector2f(0.0f,0.0f)), m_Velocity(sf::Vector2f(0.0f,0.0f)), inEngine(false)
{}

Object::~Object()
{}

Object::Object(const Object& original)
{}


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
{}

Box::Box(const Box& original)
{}
