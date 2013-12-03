#include "GravityShape.hpp"

GravityShape::GravityShape()
:m_nbPoints(0)
{

}

GravityShape::~GravityShape()
{
    //dtor
}

void GravityShape::addPoints(sf::Vector2f point)
{
   // setPoint(m_nbPoints, point);
    m_nbPoints++;
   // setPointCount(m_nbPoints);
}


bool GravityShape::isCollide(const sf::FloatRect& rect)
{
}
