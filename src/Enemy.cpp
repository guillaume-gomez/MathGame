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

#include "Enemy.hpp"

Enemy::Enemy()
    : m_model(true, sf::Vector2f(0.0f, 0.0f), 12),
      m_view(m_model,GraphScale)
{
    m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
    m_type = TypeObject::Enemy;

    m_model.setAngle(0.0f);
}

Enemy::Enemy(const Enemy& copy)
    :m_model(copy.m_model), m_view(m_model, GraphScale)
{
    m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
    m_type = TypeObject::Enemy;

    m_model.setAngle(0.0f);

}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
{
    m_model.handle_input(event, textAreaFunction);
}

void Enemy::show()
{
    m_view.setStringAttempt(m_model.getNbAttemptStr());
    m_view.show();
}

void Enemy::setDirection(bool _dir)
{
    m_model.setDirection(_dir);
    /*bad conception : we have a variable to check if the enemy should be positioned to the right in the model
      and the opposite in view !?!

     will be corrected later
    */
    m_view.setDirection(!_dir);
}

void Enemy::draw(sf::RenderTarget& app)
{
    m_view.draw(app);
}

void Enemy::reset()
{
#ifdef DEBUG

//// std::cout << " caca caca caca caca caca caca" << std::endl;
#endif
    // std::cout << m_model.getPhysicsBox().getVelocity().x << std::endl;
    m_model.setCoords(sf::Vector2f(0.0f, 0.0f));
    m_model.setAngle(0.0f);
}

EditorObject* Enemy::clone() const
{
    return new Enemy(*this);
}

EditorObject* Enemy::loadView(const Element& elmt, float scale)
{
    Enemy* newEnemy = new Enemy();
    newEnemy->setPosition(elmt.getCoord().x /*- widthTex*/ ,  elmt.getCoord().y /* - heightTex*/);
    newEnemy->setNbAttempt(elmt.getAttempt());
//    newEnemy->setDirection(elmt.setDirection());
    return newEnemy;
}

std::string Enemy::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << m_model.getNbAttemptStr() << std::endl;
    flux << m_model.getDirection() << std::endl;
    flux << m_model.getCoords().x  << " " << m_model.getCoords().y  << std::endl;
    return flux.str();
}
