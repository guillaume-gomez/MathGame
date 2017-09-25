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

#include "EnemyView.hpp"
#include <sstream>

EnemyView::EnemyView(const EnemyModel& model, float scale)
    :CharacterView(model,scale)
{
    m_nbAttempt.setColor(sf::Color(0,0,0,240));
    m_nbAttempt.setFont(14);
}

EnemyView::~EnemyView()
{
    //dtor
}

void EnemyView::draw( sf::RenderTarget& target)
{
    if(m_model.isAlive())
    {
        CharacterView::draw(target);
        m_nbAttempt.draw(target);
    }
}

void EnemyView::setStringAttempt( std::string str)
{
    m_nbAttempt.setString(str);
}

void EnemyView::show()
{
    CharacterView::show();

    //// std::cout << " m_model-->" << &m_model <<"(" << m_model.getCoords().x <<" , " << m_model.getCoords().y << ") " << std::endl;
    sf::Vector2f pos =  m_model.getCoords() * m_scale;
    sf::FloatRect rect = m_animation.getLocalBounds();

    pos.x -=  (m_nbAttempt.getText().getLocalBounds().width / 2);
    pos.y = - pos.y - rect.height - (m_nbAttempt.getText().getLocalBounds().height / 2) - offsetNbAttemptEnemy;
    m_nbAttempt.setPosition(pos);

    //setStringAttempt Done in the upper class

}

EnemyView::EnemyView(const EnemyView& copy)
    :CharacterView(copy.m_model,copy.m_scale)
//share the same texture for all the instance
// m_ArtTexture(copy.m_ArtTexture)
{
    m_nbAttempt.setColor(sf::Color(0,0,0,240));
    m_nbAttempt.setFont(14);
}
