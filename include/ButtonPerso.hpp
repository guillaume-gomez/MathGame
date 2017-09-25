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

#ifndef BUTTONPERSO_H
#define BUTTONPERSO_H

#ifdef DEBUG
#include <iostream>
#endif //DEBUG
#include <string>


#include <SFML/Graphics.hpp>

#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"

class ButtonPerso :  public sf::Sprite
{
public:
    ButtonPerso(const char* _filename = "");
    virtual ~ButtonPerso();
    void handle_input(sf::Event& event, sf::RenderTarget& target);
    void setAlpha (int _alpha);
    void draw(sf::RenderTarget& app);
    bool isClicked() const;
    void unclick();

protected:
    std::string m_filename;
    bool m_clicked;
    sf::Texture m_texture;
};

/**
*
**/

inline bool ButtonPerso::isClicked() const
{
    return m_clicked;
};

inline void ButtonPerso::setAlpha (int _alpha)
{
    this->setColor(sf::Color(255, 255, 255, _alpha));
}

inline void ButtonPerso::unclick()
{
    m_clicked = false;
}

#endif // BUTTON_H
