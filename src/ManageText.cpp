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

#include "ManageText.hpp"

ManageText::ManageText()
    :m_changed(false), m_sizeFont(Font), m_isTyping(false), m_jumpable(false), m_toResize(0)
{
    if (!m_font.loadFromFile(FilenameFont))
    {
#ifdef DEBUG
        std::cerr << "Error : ManageText::ManageText()" << std::endl;
#endif // DEBUG
    }
    m_text.setCharacterSize(m_sizeFont);
    m_text.setFont(m_font);
}


ManageText::~ManageText()
{
    //dtor
}

/**
*@brief : Draw the string
**/
void ManageText::draw(sf::RenderTarget& App)
{
    m_text.setString(m_string);
    App.draw(m_text);
}


void ManageText::handle_input(const sf::Event &event, GraphView& view)
{
    m_isTyping = false;
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
        case sf::Keyboard::BackSpace:
            m_isTyping = true;
            if(m_string.getSize() > 0)
            {
                if ( m_string[m_string.getSize() - 1] == '\n')
                {
                    m_toResize = -1;
                }

                m_string.erase(m_string.getSize() - 1);
                m_changed = true;
            }
            break;

        default:
            break;
        }
    }

    if(event.type == sf::Event::TextEntered)
    {
        if(isprint(event.text.unicode))
        {
            sf::String temp(event.text.unicode);
            m_string += temp;
            m_changed = true;
            m_isTyping = true;
        }
    }
    m_text.setString(m_string);

}

std::ostream& operator<<(std::ostream &flux, const ManageText&  texte)
{
    flux <<" x = "<< texte.m_text.getPosition().x << " y = " << texte.m_text.getPosition().y << std::endl;
    flux << " width = " << texte.m_text.getLocalBounds().width << " height = " << texte.m_text.getLocalBounds().height << std::endl;
    return flux;
}
