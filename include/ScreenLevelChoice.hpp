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

#ifndef SCREENLEVELCHOICE_H
#define SCREENLEVELCHOICE_H

#include <sstream>
#include <vector>

#include <SFGUI/SFGUI.hpp>

#include "../files.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "Screen.hpp"
#include "ScreenLink.hpp"


class SelectLevel
{
public:
    friend class ScreenLevelChoice;
    SelectLevel(ScreenLink* _stat, unsigned int level = 1, Difficulty difficulty = Normal);
    ~SelectLevel();
    virtual void selectingLevel();
    inline void setGameMode(GameMode _g)
    {
        m_modeSelectLevel = _g;
    };
    inline bool isClicked()const
    {
        return m_isClicked;
    };
    inline void unclicked()
    {
        m_isClicked = false;
    };
private:
    ScreenLink* m_stat;
    Difficulty m_difficulty;
    unsigned int m_level;
    GameMode m_modeSelectLevel;
    bool m_isClicked;

};


class ScreenLevelChoice : public Screen
{
public:
    friend class SelectLevel;
    ScreenLevelChoice(ScreenLink* _stat);
    virtual ~ScreenLevelChoice();

    virtual int Run(sf::RenderWindow & App) = 0 ;

protected:
    void loadLevelUnlocked();

    sf::Sprite m_background;
    int m_changingMenu;
    sf::Sprite m_easyBar;
    sf::Texture m_easyTex;
    sfg::Frame::Ptr m_frameEasy;
    sfg::Frame::Ptr m_frameNormal;
    sfg::Frame::Ptr m_frameHard;
    sf::Sprite m_hardBar;
    sf::Texture m_hardTex;
    sf::Sprite m_normalBar;
    sf::Texture m_normalTex;
    sfg::Box::Ptr m_layoutEasy;
    sfg::Box::Ptr m_layoutNormal;
    sfg::Box::Ptr m_layoutHard;
    bool m_playing;
    sfg::Box::Ptr m_scrolled_window_box;
    std::vector<SelectLevel*> m_selectionLevel;
    sfg::SFGUI m_sfgui;
    sfg::Window::Ptr m_window;
    ScreenLink* m_stat;
};
#endif // SCREENLEVELCHOICE_H
