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

#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#ifdef DEBUG
#include <iostream>
#endif //DEBUG
#include <string>
#include <vector>
#include <stdexcept>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../files.hpp"
#include "Enemy.hpp"
#include "Integral.hpp"
#include "LevelModel.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "GravityCircle.hpp"
#include "InfoDisplayer.hpp"
#include "ManageFunctions.hpp"
#include "Point.hpp"


class LevelView
{
public:
    LevelView(const LevelModel& model,  float _scale);
    virtual ~LevelView();
    void draw( sf::RenderTarget& target );
    std::vector<EditorObject*> getSpriteList () const;
    void loadCoord();
    void reset();

    void setView(const sf::View& view);
private:
    LevelView();
    std::vector<EditorObject*> m_listSprite;
    std::vector<std::string> m_listFunctionLevel;
    const LevelModel& m_model;
    static sf::Texture m_texNormal;
    static sf::Texture m_texGoal;
    float m_scale;
    static bool TexturesLoaded;
    static bool loadTex(const char* _filenameNormalText = FilenameNormalPointTex, const char* _filenameGoalText = FilenamePointGoalTex);

    sf::View m_view;
};

/****************************************************
**
******************************************************/

inline std::vector<EditorObject*> LevelView::getSpriteList () const
{
    return m_listSprite;
};

inline void LevelView::setView(const sf::View& view)
{
    m_view = view;
}

/****************************************************
**
******************************************************/

#endif // LEVELVIEW_H
