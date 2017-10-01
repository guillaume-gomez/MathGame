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

#ifndef INFODISPLAYER_H
#define INFODISPLAYER_H

#include "EditorObject.hpp"
#include "../libs/TextAreaSFML2_0.hpp"

class InfoDisplayer : public EditorObject
{
public:
    InfoDisplayer();
    virtual ~InfoDisplayer();
    InfoDisplayer(const InfoDisplayer& copy);

    void setMessage(std::string message);
    std::string getMessage() const;
    virtual void draw(sf::RenderTarget& app);
    virtual EditorObject* clone() const;
    virtual void setPosition(float x, float y);
    virtual void setPosition(sf::Vector2f& pos);
    virtual sf::FloatRect get_GlobalBounds() const;
    virtual sf::Vector2f get_Position() const;
    virtual std::string save(float scale = GraphScale) const;
    virtual EditorObject* loadView(const Element& elmt, float scale);

private:
    std::string m_message;
    TextAreaSFML2_0 m_area;

};


inline void InfoDisplayer::setMessage(std::string message)
{
    m_message = message;
    m_area.setString(m_message);
    m_area.scaleBG();
}


inline std::string InfoDisplayer::getMessage() const
{
    return m_message;
}


#endif // INFODISPLAYER_H
