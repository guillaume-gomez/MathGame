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

#ifndef SCREENOPTION_H
#define SCREENOPTION_H

#include <fstream>
#include <vector>

#include "AniSprite.hpp"
#include "../constants.hpp"
#include "../files.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "Screen.hpp"

#include <SFGUI/SFGUI.hpp>


#define FOR_STL_REVERSE_ITERATOR(container_type, name, iteratorName) for(container_type::reverse_iterator iteratorName=name.rbegin(); iteratorName!=name.rend(); iteratorName++)
class ChoiceCharacter
{
public:
    ChoiceCharacter(unsigned int type = 13);
    void defineCharacter();
    ~ChoiceCharacter();
private:
    unsigned int m_type;
};


class ScreenOption : public Screen
{
public:
    static std::string m_filenameChar;
    ScreenOption(unsigned int nbButon = 3);
    void activateSliding();
    void desactivateSliding();
    void save();
    void quit();
    virtual ~ScreenOption();
    int Run(sf::RenderWindow& app);
    inline std::string getFilenameChar()const
    {
        return m_filenameChar;
    };
    inline void setFilenameChar(std::string str)
    {
        m_filenameChar = str;
    };

private:
    sf::Sprite m_background;
    sfg::Box::Ptr m_box;
    sfg::Box::Ptr m_boxClose;
    std::vector<ChoiceCharacter> m_character_array;
    AniSprite currentChoice;
    std::string m_gravityType;
    sfg::Frame::Ptr m_frameCharacter;
    sfg::Frame::Ptr m_framePhysics;
    sfg::Box::Ptr m_layoutCharacter;
    sfg::Box::Ptr m_layoutPhysics;
    unsigned int m_nbButton;
    sfg::SFGUI m_sfgui;
    sfg::Window::Ptr m_window;
    bool m_quit;
    unsigned int valeur;
};
#endif // SCREENOPTION_H
