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

#ifndef MANAGELEVEL_H
#define MANAGELEVEL_H

#include "../constants.hpp"
#include "../files.hpp"
#include "LevelView.hpp"
#include "LevelModel.hpp"
#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <fstream>
#include <sstream>
#include <string>


#include "ConstrueFunction.hpp"
#include "CharacterModel.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "ScreenLink.hpp"

class ManageLevel
{
    public:
        float m_scale;

        ManageLevel(unsigned int _level = 1 , Difficulty _diff = Normal, float m_scale = 1.0f);
        void loadFile(int numLevel, GameMode mode);
        void loadLevel();
        virtual ~ManageLevel();
        void setLevel(int _level);
        unsigned int getLevel() const;
        void IsNextLevel();
        int changeLevel(ScreenLink * link);
        void reset();
        void drawPoints(sf::RenderTarget& app);
        void drawUI(sf::RenderTarget& app);
        std::string convertEnum (Difficulty _diff);
        void displaying(sf::Event& event, sf::RenderTarget& target, sf::View& myView);
        void levelFinished (const CharacterModel& charModel, bool& soundPlayable);
        void setToolTipPos (sf::Vector2f _temp);
        sf::Vector2f getToolTipPos ()const;
        void setToolTipScale (sf::Vector2f _scale);
        sf::Vector2f getToolTipScale ()const;
        void decrementAttempt();
        bool getChangeLevel()const ;
        void displayNbAttempt();
        void setnbAttempTextPosition(sf::Vector2f _pos);
        void setnbAttempTextScale(sf::Vector2f _pos);
        void setDiff(Difficulty _diff);
        void showEnemies();
        void initEnemies();
        void handle_inputEnnemies(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
        void fillLevelFunctions(ManageFunctions& func);
        const std::vector<EditorObject*> getSpriteList () const;
        void scaleNbAttempt(float scaleX, float scaleY);
        void receiveView(const sf::View& view);
        sf::Vector2f getInitialPosition() const;

    private:
        Difficulty m_difficulty;
        std::string m_filenameCurrent;
        sf::Font m_font;
        unsigned int m_levelCurrent;
        bool m_changeLevel;
        LevelModel* m_levelModel;
        LevelView* m_levelView;
        bool m_isDisplayToolTip;
        sf::Text m_nbAttemp;
        sf::String m_string;
        sf::Text m_text;
        sf::Sprite m_tooltip;
        static sf::Texture toolTipTex;
        static bool toolTipTexLoaded;
        static bool loadToolTipTex(const char* filenametoolTipTex = FilenameToolTipTex);
};

/*********************************************************/
//       Accessors
/*********************************************************/

inline void ManageLevel::setLevel(int _level)
{
    m_levelCurrent = _level;
}

inline unsigned int ManageLevel::getLevel() const
{
    return m_levelCurrent;
}

inline void ManageLevel::setToolTipPos (sf::Vector2f _temp)
{
    m_tooltip.setPosition(_temp);
}

inline sf::Vector2f ManageLevel::getToolTipPos() const
{
    return m_tooltip.getPosition();
}

inline void ManageLevel::setToolTipScale (sf::Vector2f _scale)
{
    m_tooltip.setScale(_scale);
}

inline sf::Vector2f ManageLevel::getToolTipScale() const
{
    return m_tooltip.getScale();
}

inline bool ManageLevel::getChangeLevel() const {return m_changeLevel;};

inline void ManageLevel::setnbAttempTextPosition(sf::Vector2f _pos)
{
    m_nbAttemp.setPosition(_pos);
};

inline void ManageLevel::setnbAttempTextScale(sf::Vector2f _pos)
{
    m_nbAttemp.setScale(_pos);
};

inline void ManageLevel::setDiff(Difficulty _diff)
{
    m_difficulty = _diff;
}

const inline std::vector<EditorObject*> ManageLevel::getSpriteList () const
{
    return m_levelView->getSpriteList();
}

inline void ManageLevel::receiveView(const sf::View& view)
{
    m_levelView->setView(view);
}

inline sf::Vector2f ManageLevel::getInitialPosition() const
{
    return m_levelModel->getInitialPosition();
}

/*********************************************************/
//      Accessors
/********************************************************/
#endif // MANAGELEVEL_H
