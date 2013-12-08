#include "Point.hpp"


Point::Point(float radius, float scale, std::string filename)
:EditorObject()
{
   sf::Texture * texture = 0;
   texture = TextureManager::getTextureManager()->getResource(std::string(filename));

   if(texture)
   {
        this->setTexture(texture);
   }
   else
   {
    std::cout << "Warning : in the class Point, Constructor didn't find the texture file" << filename << std::endl;
   }
    this->setRadius(radius);
    this->setOrigin(radius, radius);
    this->setScale(GraphScale, GraphScale);
    this->setFillColor(sf::Color(0,0,0,100));
}

Point::Point()
{

}

Point::~Point()
{
    //dtor
}

