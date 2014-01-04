#include "Point.hpp"


Point::Point(float radius,bool goalPoint, float scale, std::string filename)
:EditorCircle(), m_goalPoint(goalPoint)
{
   sf::Texture * texture = nullptr;
   texture = TextureManager::getTextureManager()->getResource(std::string(filename));

   if(texture)
   {
        this->setTexture(texture);
   }
   else
   {
        std::cout << "Warning : in the class Point, Constructor didn't find the texture file" << filename << std::endl;
    /*if(m_goalPoint)
        {
            this->setFillColor(sf::Color(255, 0, 0));
        }
        else
        {
            this->setFillColor(sf::Color(0, 0, 0));
        }*/
   }

   if(m_goalPoint)
    {
            this->m_type = TypeObject::GoalPoint;
            this->setFillColor(sf::Color(255, 0, 0));
    }
    else
    {
            this->m_type = TypeObject::Point;
            this->setFillColor(sf::Color(0, 0, 0));
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

Point::~Point()
{
    //dtor
}

