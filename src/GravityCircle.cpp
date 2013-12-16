#include "GravityCircle.hpp"
#include <stdexcept>
#include <iostream>

GravityCircle::GravityCircle(float _radius, float radiusMax, bool defOriginCenter, std::string filename)
:EditorCircle(), m_filename(filename),m_radiusMax(radiusMax), m_texture(*TextureManager::getTextureManager()->getResource("resources/sprites/smiley.png"))
{
    if(_radius > 0.0f)
    {
        this->m_type = TypeObject::CIRCLE;
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
    else
    {
        throw std::runtime_error("An instance of GravityCircle can't be created because the radius is equal to zero");
    }

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
