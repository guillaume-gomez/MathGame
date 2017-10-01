/*
 *  A 2D video game in C++ with SFML where platforms are actually Maths Curves resulting of equations you write
 *  Copyright (C) 2013,2017  Gomez Guillaume, Jarretier Adrien
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.*
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact us on Github : https://github.com/guillaume-gomez/MathGame
 *                      or https://github.com/AdrienJarretier
 */

#include "EditorCircle.hpp"
#include <sstream>

EditorCircle::EditorCircle()
    :EditorObject()
{
    this->m_type = TypeObject::Abstract;
//    #ifdef DEBUG
//        std::cout << "================================================" << &m_physicsCircle << std::endl;
//        std::cout << "EditorCircle::EditorCircle()::m_physicsCircle : " << &m_physicsCircle << std::endl;
//    #endif // DEBUG
//    Physics::Engine::getEngine()->addObject(&m_physicsCircle);
}

EditorCircle::EditorCircle(const EditorCircle& original)
    :EditorObject(original)
{
    this->m_type = TypeObject::Abstract;
//    Physics::Engine::getEngine()->addObject(&m_physicsCircle);
}

EditorCircle::~EditorCircle()
{
    //dtor
//	Physics::Engine::getEngine()->delObject(&m_physicsCircle);
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
    flux << this->getPosition().x / scale <<" " << - this->getPosition().y / scale << std::endl;
    return flux.str();
}

void EditorCircle::draw(sf::RenderTarget& app)
{
//    #ifdef DEBUG
//        std::cout << "mkjjdffguijuhdgdjfsgftrbhjgfjhsfggfvfiudfdsegfedgefgyufeufqgfqgfqegqfegy" << std::endl;
//        std::cout << "EditorCircle::m_physicsCircle : " << &m_physicsCircle << std::endl;
//    #endif // DEBUG
//    CircleShape::setPosition(m_physicsCircle.getPosition()); C'était un test
    app.draw(*this);
}

void EditorCircle::setRadius(float radius)
{
//    #ifdef DEBUG
//        std::cout << "setRadius" << std::endl;
//    #endif // DEBUG
    CircleShape::setRadius(radius);
    m_physicsCircle.setRadius(radius);
}
