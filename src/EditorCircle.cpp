#include "EditorCircle.hpp"
#include <sstream>

EditorCircle::EditorCircle()
:EditorObject()
{
    this->m_type = TypeObject::Abstract;
}

EditorCircle::~EditorCircle()
{
    //dtor
}


float EditorCircle::distance(sf::Vector2f pointOne, sf::Vector2f pointTwo)
{
    //Return the distance between the two points
    if(pointOne != sf::Vector2f(0.0f,0.0f) || pointTwo != sf::Vector2f(0.0f,0.0f))
    {
        return sqrt(pow(pointTwo.x - pointOne.x, 2) + pow(pointTwo.y - pointOne.y, 2));
    }
    return 0.0f;
}


bool EditorCircle::isCollide(sf::Vector2f point)
{
    sf::Vector2f position = this->getPosition();
    if(distance(position, point) < this->getRadius())
    {
        return true;
    }
    return false;
}

bool EditorCircle::isCollide(const sf::FloatRect& rect)
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

std::string EditorCircle::save(float scale) const
{
  std::stringstream flux;
  flux << this->getPosition().x / scale <<" " << this->getPosition().y / scale << std::endl;
  return flux.str();
}

void EditorCircle::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}


