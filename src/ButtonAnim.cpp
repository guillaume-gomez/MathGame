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

#include "ButtonAnim.hpp"

ButtonAnim::ButtonAnim(const char* _filename, int _widthFrame,int _heightFrame)
    :ButtonPerso(_filename), m_changing(true)
{
    if (m_texture.loadFromFile(_filename))
    {
        m_spriteList.setTexture(m_texture);
        m_spriteList.SetFrameSize(_widthFrame,_heightFrame);
    }
    else
    {
#ifdef DEBUG
        std::cerr << "In constructor of ButtonAnim :Texture don't loaded (revoir les cours d'anglais)" << std::endl;
#endif // DEBUG
    }
}

void ButtonAnim::handle_input(sf::Event& event,sf::RenderTarget& target)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        sf::Vector2f coord = target.mapPixelToCoords((sf::Vector2i(x, y)));

        if(getGlobalBounds().contains(coord.x, coord.y))
        {
            m_changing = true;
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
        }
        else
        {
            setAlpha(Blur);
        }
    }
}

void ButtonAnim::Launch()
{
    m_spriteList.Play();
}

void ButtonAnim::switchTile()
{
    if(m_changing)
    {
        int nbSprite = m_spriteList.GetFrameCount();
        int _currentFrame = m_spriteList.getCurrentFrame();
        m_spriteList.setCurrentFrame(_currentFrame+1);
        this->setTextureRect(m_spriteList.GetFramePosition(_currentFrame % nbSprite));
        m_changing = false;
    }

}

/*void ButtonAnim::draw(sf::RenderTarget& target)
{
    target.draw(this);
}*/

ButtonAnim::~ButtonAnim()
{
    //dtor
}
