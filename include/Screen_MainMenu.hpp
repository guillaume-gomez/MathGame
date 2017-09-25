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

#ifndef SCREEN_MAINMENU_H
#define SCREEN_MAINMENU_H

#include <SFGUI/SFGUI.hpp>

#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "ScreenLink.hpp"
#include "Screen.hpp"


//#define ASSISTED_MODE_ACTIVATED

class Screen_MainMenu : public Screen
{
public:
    Screen_MainMenu();
    virtual ~Screen_MainMenu();
    virtual int Run(sf::RenderWindow & App);

    void playButtonClick();
    void play2ButtonClick();
    void creditButtonClick();
    void editorButtonClick();
    void optionButtonClick();
    void howToButtonClick();
    void resize(float scaleX, float scaleY,sf::RenderWindow& App);
protected:
private:
    int m_alpha_max;
    int m_alpha_div;
    sf::Sprite m_background;
    bool m_playing;
    int m_changingMenu;
    sfg::Button::Ptr m_credit_button;
    sfg::Button::Ptr m_editor_button;

#ifdef ASSISTED_MODE_ACTIVATED
    sfg::Button::Ptr m_play_button;
#endif // ASSISTED_MODE_ACTIVATED

    sfg::Button::Ptr m_play2_button;
    sfg::Button::Ptr m_option_button;
    sfg::Button::Ptr m_howTo_button;
    sfg::SFGUI m_sfgui;
    sfg::Window::Ptr m_window;

};

#endif // SCREEN_MAINMENU_H
