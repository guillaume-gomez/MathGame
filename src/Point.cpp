#include "Point.hpp"


Point::Point(float radius,bool goalPoint, float scale, std::string filename)
:EditorCircle(), m_goalPoint(goalPoint)
{
   sf::Texture * texture = 0;
   texture = TextureManager::getTextureManager()->getResource(std::string(filename));

   if(texture)
   {
        this->setTexture(texture);
        std::cout << "YYY" << m_goalPoint << std::endl;
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
            this->m_type = TypeObject::GOALPOINT;
            this->setFillColor(sf::Color(255, 0, 0));
        }
        else
        {
            this->m_type = TypeObject::POINT;
            this->setFillColor(sf::Color(0, 0, 0));
        }
    this->setRadius(radius);
    this->setOrigin(radius, radius);
    this->setScale(GraphScale, GraphScale);
}

Point::Point()
{

}

Point::~Point()
{
    //dtor
}

