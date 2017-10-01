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

#include "EnemyModel.hpp"

EnemyModel::EnemyModel(bool life, sf::Vector2f coord, float speed, MoveType moveType, unsigned int _nbActive)
    :CharacterModel(life,coord,speed,moveType), m_nbAttempt(_nbActive),m_isActive(false)
{
    if(m_nbAttempt == 0)
    {
        m_isActive = true;
    }

}

EnemyModel::EnemyModel(const EnemyModel& copy)
    :CharacterModel(copy.m_life, copy.getCoords(), copy.m_speed, copy.m_moveType),
     m_nbAttempt(copy.m_nbAttempt), m_isActive(copy.m_isActive)
{
    if(m_nbAttempt == 0)
    {
        m_isActive = true;
    }
}

EnemyModel::~EnemyModel()
{
    //dtor
}

void EnemyModel::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
{
    if(isActive())
    {
        //  CharacterModel::handle_input(event,textAreaFunction);
    }
    if(isActive())
    {
        float speed = 0;
        if(m_orientedRight)
        {
            speed = m_speed;
        }
        else
        {
            speed = - m_speed;
        }
        m_PhysicsBox.setThrust(sf::Vector2f(speed, m_PhysicsBox.getThrust().y));
    }
}


void EnemyModel::decrementAttempt()
{
    if(m_nbAttempt > 0)
    {
        m_nbAttempt--;
        if(m_nbAttempt == 0)
        {
            m_isActive = true;
        }
    }
}


bool EnemyModel::isActive()const
{
    return m_isActive;
}

unsigned int EnemyModel::getNbAttempt() const
{
    return m_nbAttempt;
}


std::string EnemyModel::getNbAttemptStr() const
{
    std::ostringstream oss;
    //// std::cout << "EnemyModel::getNbAttemptStr"<< m_nbAttempt << std::endl;
    oss << getNbAttempt();
    return oss.str();
}
