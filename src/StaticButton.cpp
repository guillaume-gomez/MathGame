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

#include "StaticButton.hpp"

StaticButton::StaticButton(const char* _filename)
:m_filename(_filename), m_clicked(false), m_isFocused(false)
{
    sf::Texture * texture = nullptr;
    texture = TextureManager::getTextureManager()->getResource(std::string(m_filename));
    if(texture)
    {
        this->setTexture(*texture);
    }
    /*else
    {
        // std::cout << "Warning : in StaticButton, Constructor didn't find a file texture " << m_filename << std::endl;
    }*/
}

void StaticButton::handle_input(sf::Event& event,sf::RenderTarget& target)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)));

        if(getGlobalBounds().contains(coord.x, coord.y))
        {
            m_clicked = true;
        }
    }

    else if(event.type == sf::Event::MouseButtonReleased)
    {
        m_clicked = false;
    }

    else if(event.type == sf::Event::MouseMoved)
    {
        int x =  event.mouseMove.x;
        int y =  event.mouseMove.y;
        sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)));

        if(getGlobalBounds().contains(coord.x, coord.y))
        {
            setAlpha(Clear);
            m_isFocused = true;
        }
        else
        {
            setAlpha(Blur);
            m_isFocused = false;
        }
    }
}


void StaticButton::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}

StaticButton::~StaticButton()
{
    //dtor
}
