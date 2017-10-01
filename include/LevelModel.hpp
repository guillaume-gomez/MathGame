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

#ifndef LEVELMODEL_H
#define LEVELMODEL_H

#ifdef DEBUG
#include <iostream>
#endif //DEBUG
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "../constants.hpp"
#include "CharacterModel.hpp"
#include "EditorCircle.hpp"
#include "Element.hpp"

//note : la last points read in a file is the goal to reach
class LevelModel
{
public:
    LevelModel(std::string _filename = "", GameMode mode = Classic );
    virtual ~LevelModel();
    bool isWin() const;
    bool IsLose() const;
    sf::Vector2f getGoalCoord()const;
    unsigned int getNbPoints() const;
    float getRadius(unsigned int i) const;
    TypeObject getType(unsigned int i) const;
    sf::Vector2f getCoordPoints(unsigned int i) const ;
    void IsFinishing (const CharacterModel& charactermodel, float _scale , bool& playableSound);
    bool getSens(unsigned int i) const;
    unsigned int getAttempt(unsigned int i) const;
    bool getCheckValue(unsigned int i)const;
    void IsLosing();
    friend std::ostream& operator<<(std::ostream &flux, const LevelModel& level);
    unsigned int getNbAttempt()const;
    float getEnd(unsigned int i) const;
    float getBegin(unsigned int i) const;
    std::string getFunction(unsigned int i) const;
    std::string getMessage(unsigned int i) const;
    void decrementAttempt();
    void reset();
    int getSaveAttempt()const;
    void setMode(GameMode _mode);
    GameMode getMode() const;
    std::vector<std::string> getVectorFunctions();

private:
    LevelModel();
    /* the Level file is sorted by type of element.
    Points and obviously GoalPoint are at the end of the file, so the variable m_beginPoint detect the first Point to check during the game
    the good colission.
    */
    unsigned int m_beginPoint;
    std::vector<Element> m_coordElements;
    std::ifstream m_fileLevel;
    unsigned int m_nbElements;
    bool m_win;
    bool m_lose;
    int m_nbAttempt;
    GameMode m_mode;
    std::vector<bool> m_pointsCheck;
    int m_saveNbAttemp;
};

/******************************************************************************
*                     Accessors
*******************************************************************************/
inline bool LevelModel::isWin() const
{
    return m_win;
};

inline bool LevelModel::IsLose() const
{
    return m_lose;
};

inline unsigned int LevelModel::getNbPoints() const
{
    return m_nbElements;
};


inline sf::Vector2f LevelModel::getCoordPoints(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getCoord();
    }
    return sf::Vector2f(-1.0f, -1.0f);
};


inline sf::Vector2f LevelModel::getGoalCoord() const
{
    if(m_coordElements.size() > 0)
        return m_coordElements[m_coordElements.size() - 1].getCoord();
    else
        return sf::Vector2f(0.0f, 0.0f);

}


// add the test if it is a circle
inline float LevelModel::getRadius(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getRadius();
    }
    return -1;
}

inline TypeObject LevelModel::getType(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getType();
    }
    return TypeObject::Abstract;
}

inline bool LevelModel::getSens(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getSens();
    }
    return true;
}

inline unsigned int LevelModel::getAttempt(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getAttempt();
    }
    return 1;
}

inline std::string LevelModel::getFunction(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getFunction();
    }
    return std::string();
}

inline std::string LevelModel::getMessage(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getMessage();
    }
    return std::string();
}

inline float LevelModel::getBegin(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getBegin();
    }
    return -10000.0f;
}

inline float LevelModel::getEnd(unsigned int i) const
{
    if (i < m_coordElements.size())
    {
        return m_coordElements[ i ].getEnd();
    }
    return 10000.0f;
}


inline bool LevelModel::getCheckValue(unsigned int i)const
{
    if (i < m_pointsCheck.size())
    {
        return m_pointsCheck[i];
    }
    return false;
}

inline unsigned int LevelModel::getNbAttempt() const
{
    return m_nbAttempt;
};

inline void LevelModel::decrementAttempt()
{
    m_nbAttempt--;
};

inline int LevelModel::getSaveAttempt() const
{
    return m_saveNbAttemp;
};

inline void LevelModel::setMode(GameMode _mode)
{
    m_mode = _mode;
};

inline GameMode LevelModel::getMode() const
{
    return  m_mode;
};

/******************************************************************************
*                     Accessors
*******************************************************************************/
#endif // LEVELMODEL_H
