#include "GravityCircle.hpp"
#include <iostream>

GravityCircle::GravityCircle(float _radius, float radiusMax, bool defOriginCenter, std::string filename)
:m_filename(filename),m_radiusMax(radiusMax), m_texture(*TextureManager::getTextureManager()->getResource("resources/sprites/smiley.png"))
{
    this->setRadius(_radius);
    if(defOriginCenter)
    {
        this->setOrigin(_radius,_radius);
    }

    if(radiusMax < _radius)
    {
        radiusMax = _radius;
    }

    this->setTexture(&m_texture);

}

void GravityCircle::grow(float step)
{
    float currentRadius = this->getRadius();
    if(currentRadius < m_radiusMax)
    {
        this->setRadius(currentRadius + step);
        this->setOrigin(currentRadius + step,currentRadius + step);
    }
}

GravityCircle::~GravityCircle()
{
    //dtor
}
