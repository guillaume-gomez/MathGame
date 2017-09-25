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

#include "InfoDisplayer.hpp"
#include <sstream>

InfoDisplayer::InfoDisplayer()
    :EditorObject(),
     m_message("")
{
    this->m_type = TypeObject::Info;
    m_area.setCharacterSize(12);
    m_area.blinkCaret(0);
    m_area.setAlphaColor(125);
    m_area.setPaddingBottom(20);
    m_area.setPaddingTop(20);
    m_area.setBackgroundTexture(FilenamePanelInfoTex);
}

InfoDisplayer::~InfoDisplayer()
{
    //dtor
}


InfoDisplayer::InfoDisplayer(const InfoDisplayer& copy)
    :EditorObject(),
     m_message(copy.m_message),
     m_area(copy.m_area)
{
    this->m_type = TypeObject::Info;
}

void InfoDisplayer::draw(sf::RenderTarget& app)
{
    m_area.draw(app);
}

EditorObject* InfoDisplayer::clone() const
{
    return new InfoDisplayer(*this);
}

void InfoDisplayer::setPosition(float x, float y)
{
    m_area.setPosition(x,y);
}


void InfoDisplayer::setPosition(sf::Vector2f& pos)
{
    this->setPosition(pos.x, pos.y);
}

sf::FloatRect InfoDisplayer::get_GlobalBounds() const
{
    return m_area.getGlobalBounds();
}

sf::Vector2f InfoDisplayer::get_Position() const
{
    return m_area.getPosition();
}

std::string InfoDisplayer::save(float scale) const
{
    std::stringstream flux;
    flux << this->getTypeStr() << std::endl;
    flux << this->get_Position().x / scale <<" " << - this->get_Position().y / scale << std::endl;
    flux << this->getMessage() << "#"<<std::endl;
    return flux.str();
}

EditorObject* InfoDisplayer::loadView(const Element& elmt, float scale)
{
    InfoDisplayer * NewInfo =  new InfoDisplayer();
    NewInfo->setPosition(elmt.getCoord().x * scale/*- widthTex*/ , - elmt.getCoord().y * scale/* - heightTex*/);
    return NewInfo;
}
