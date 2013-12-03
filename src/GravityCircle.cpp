#include "GravityCircle.hpp"
#include <iostream>

float distance(sf::Vector2f pointOne, sf::Vector2f pointTwo)
{
    //Return the distance between the two points
    return sqrt(pow(pointTwo.x - pointOne.x, 2) + pow(pointTwo.y - pointOne.y, 2));
}

GravityCircle::GravityCircle(float _radius , bool defOriginCenter)
{
    this->setRadius(_radius);
    if(defOriginCenter)
    {
        this->setOrigin(_radius,_radius);
    }
}

GravityCircle::~GravityCircle()
{
    //dtor
}

bool GravityCircle::isCollide(const sf::FloatRect& rect)
{
    //Closest point on collision box
    sf::Vector2f closest;
    sf::Vector2f position = this->getPosition();
    //Find closest x offset
    if(position.x < rect.left)
    {
        closest.x = rect.left;
    }
    else if(position.x > rect.left + rect.width)
    {
        closest.x = rect.left + rect.width;
    }
    else
    {
        closest.x = position.x;
    }

    if(position.y < rect.top)
    {
        closest.y = rect.top;
    }
    else if(position.y > rect.top + rect.height)
    {
        closest.y = rect.top + rect.height;
    }
    else
    {
        closest.y = position.y;
    }

    if(distance(position, closest) < this->getRadius())
    {
        return true;
    }
    return false;
}

void GravityCircle::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}
