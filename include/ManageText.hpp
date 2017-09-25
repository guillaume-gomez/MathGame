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

#ifndef ManageText_H
#define ManageText_H

#ifdef DEBUG
#include <iostream>
#endif

#include <SFML/Graphics.hpp>
#include "GraphView.hpp"
#include "../files.hpp"
#include "../constants.hpp"

class ManageText
{
public:
    ManageText();
    virtual ~ManageText();
    inline int getSizeFont()const
    {
        return  m_sizeFont;
    }
    inline void setSizeFont( int _size)
    {
        m_sizeFont = _size;
    }
    inline sf::Font getFont() const
    {
        return m_font;
    }
    inline void getSizeFont( sf::Font _f)
    {
        m_font = _f;
    }
    inline sf::String getString() const
    {
        return m_string;
    }
    inline void setString ( sf::String _str)
    {
        m_string = _str;
    }
    inline void setFont ( int val)
    {
        m_sizeFont = val ;
    }
    inline void setPosition ( sf::Vector2f pos)
    {
        m_text.setPosition(pos);
    }
    inline void setAlpha ( int _a)
    {
        m_text.setColor(sf::Color(0, 0, 0, _a));
    }
    inline void setColor ( sf::Color col)
    {
        m_text.setColor(col);
    }
    inline bool isJumpable() const
    {
        return m_jumpable;
    }
    inline bool isTyping() const
    {
        return m_isTyping;
    }
    inline void setJumpable(bool  _b)
    {
        m_jumpable = _b;
    }
    inline void setToResize( int _i)
    {
        m_toResize = _i;
    }
    inline int getToResize() const
    {
        return m_toResize;
    }
    inline sf::Text getText() const
    {
        return m_text;
    }
    void handle_input(const sf::Event &event, GraphView& view);
    //void displayingMode( TextArea& textarea);
    void draw(sf::RenderTarget& App);
    // void jump( TextArea& textarea);

    bool m_changed;
    friend std::ostream& operator<<( std::ostream &flux, const ManageText&  texte );
private:
    sf::Text m_text;
    sf::Font m_font;
    int m_sizeFont;
    bool m_isTyping;
    bool m_jumpable;
    int m_toResize;
    sf::String m_string;
};

#endif // ManageText_H
