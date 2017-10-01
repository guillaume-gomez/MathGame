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

#include "Hero.hpp"
#include <sstream>

Hero::Hero()
    : m_model(true, sf::Vector2f(0.0f, 0.0f), CharSpeed),
      m_view(m_model,GraphScale)
{
#ifdef DEBUG
//        std::cout << "Hero constructor" << std::endl;
#endif // DEBUG
    this->m_type = TypeObject::Hero;

    m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
    m_model.addToEngine();
}

Hero::~Hero()
{
    //dtor
}

void Hero::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
{
    m_model.handle_input(event, textAreaFunction);
}

void Hero::show()
{
    m_view.show();
}

void Hero::draw(sf::RenderTarget& app)
{
    m_view.draw(app);
}

void Hero::reset()
{
    m_model.setCoords(sf::Vector2f(0.0f, 0.0f));
    m_model.setAngle(0.0f);
//    m_model.getPhysicsBox().jump(false);
}

Hero::Hero(const Hero& copy)
    :m_model(copy.m_model), m_view(m_model, GraphScale)
{
    m_model.setSize(m_view.getRectLocal().width, m_view.getRectLocal().height);
    m_type = TypeObject::Hero;
}

EditorObject* Hero::clone() const
{
    return new Hero(*this);
}

std::string Hero::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    //flux << m_model.getDirection() << std::endl;
    //flux << m_model.getCoords().x / scale << " " << - m_model.getCoords().y / scale << std::endl;
    return flux.str();
}
