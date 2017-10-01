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

#ifndef SCREENHOWTO_H
#define SCREENHOWTO_H

#include <fstream>
#include <ostream>

#include "Screen.hpp"
#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"

class ScreenHowTo : public Screen
{
public:
    ScreenHowTo();
    virtual int Run ( sf::RenderWindow &App);
    virtual ~ScreenHowTo();

    void loadInstruction();
    void previousClick();
    void nextClick();

    void loadFileInstruction();
    sf::Image Resize( sf::Image CurrentImage, bool keep, const sf::Vector2u& customSize);

private:
    bool m_quit;
    sf::Sprite m_background;
    sfg::Box::Ptr m_box;
    sfg::Box::Ptr m_boxImages;
    sfg::Box::Ptr m_boxLabel;
    sfg::SFGUI m_sfgui;
    sfg::Window::Ptr m_window;
    sfg::Button::Ptr m_next;
    sfg::Button::Ptr m_previous;
    sfg::Image::Ptr m_image;
    sfg::Label::Ptr m_label;
    std::vector<std::string> m_filenameImages;
    std::vector<std::string> m_instructions;
    int m_nbInstruction;
    int m_currentInstruction;
};

#endif // SCREENHOWTO_H
