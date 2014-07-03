#include "Point.hpp"
#include <sstream>


Point::Point(float radius,bool goalPoint, float scale)
:EditorCircle(), m_goalPoint(goalPoint)
{

   if(m_goalPoint)
    {
            this->m_type = TypeObject::GoalPoint;
            this->setFillColor(sf::Color(255, 0, 0));
            std::cout << "Colored in the class point" << std::endl;
    }
    else
    {
            this->m_type = TypeObject::Point;
            this->setFillColor(sf::Color(0, 0, 0));
            std::cout << "UnColored in the class point" << std::endl;
    }
    this->setRadius(radius);
    this->setOrigin(radius, radius);
    this->setScale(GraphScale, GraphScale);
}

EditorObject* Point::clone() const
{
    return new Point(*this);
}

Point::Point()
{

}

std::string Point::save(float scale) const
{
  std::stringstream flux;
  flux << this->getTypeStr() << std::endl;
  flux << EditorCircle::save(scale);
  return flux.str();
}

 EditorObject* Point::loadView(const Element& elmt, float scale)
 {
    Point * NewPoint =  new Point(sizePoint);
        NewPoint->setPosition(elmt.getCoord().x * scale/*- widthTex*/ , - elmt.getCoord().y * scale/* - heightTex*/);
        return NewPoint;
 }

Point::~Point()
{
    //dtor
}

