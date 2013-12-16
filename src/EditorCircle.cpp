#include "EditorCircle.hpp"

EditorCircle::EditorCircle()
:m_type(TypeObject::ABSTRACT)
{

}

EditorCircle::~EditorCircle()
{
    //dtor
}


float EditorCircle::distance(sf::Vector2f pointOne, sf::Vector2f pointTwo)
{
    //Return the distance between the two points
    return sqrt(pow(pointTwo.x - pointOne.x, 2) + pow(pointTwo.y - pointOne.y, 2));
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

void EditorCircle::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}



std::ostream& operator<<( std::ostream &flux, TypeObject const type )
{
    switch(type)
    {
        case TypeObject::ABSTRACT:
            flux << "Abstract";
        break;

        case TypeObject::CIRCLE:
            flux << "Circle";
        break;

        case TypeObject::POINT:
            flux << "Point";
        break;

        case TypeObject::GOALPOINT:
            flux << "Goal Point";
        break;

        default:
            flux <<" Error invalid type";
        break;

    }
    return flux;
}



std::string EditorCircle::getTypeStr() const
{
    switch(m_type)
    {
        case TypeObject::ABSTRACT:
            return "Abstract";
        break;

        case TypeObject::CIRCLE:
            return  "Circle";
        break;

        case TypeObject::POINT:
            return "Point";
        break;

        case TypeObject::GOALPOINT:
            return  "Goal Point";
        break;

        default:
            return " Error invalid type";
        break;

    }
}

