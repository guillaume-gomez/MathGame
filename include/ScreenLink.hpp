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

#ifndef ScreenLink_H
#define ScreenLink_H

#ifdef DEBUG
	#include <iostream>
#endif
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

#include "../files.hpp"
#include "../constants.hpp"

/* temporaire */
const int valEasy = 3 ;
const int valNormal = 3;
const int valHard = 1;

class ScreenLink
{
    public:
        ScreenLink();
        virtual ~ScreenLink();
        void countNbFiles();
        void load();
        void save();
        friend std::ostream& operator<<( std::ostream &flux, const ScreenLink&  stat );
        void setMaxLevel(Difficulty type , unsigned int val );
        unsigned int getMaxLevel(Difficulty type) const;
        void setCurrentLevel(unsigned int level);
        void setParamLevel( Difficulty _diff, unsigned int level, GameMode mode);
        unsigned int getCurrentLevel()const;
        Difficulty getDiff()const;
        unsigned int getNbFiles()const;
        GameMode getMode()const;
         void setnbFiles( unsigned int _nb);

    private:
        unsigned int m_currentLevel;
        Difficulty m_difficulty;
        unsigned int m_maxEasy;
        unsigned int m_maxNormal;
        unsigned int m_maxHard;
        unsigned int m_nbFile;
        GameMode m_modeChoose;
};

inline void ScreenLink::setParamLevel(Difficulty _diff, unsigned int level, GameMode mode)
{
    m_difficulty = _diff;
    m_currentLevel = level;
    m_modeChoose = mode;
}

inline unsigned int ScreenLink::getCurrentLevel() const
{
    return m_currentLevel;
}

inline void ScreenLink::setCurrentLevel(unsigned int level)
{
    m_currentLevel = level;
}

inline Difficulty ScreenLink::getDiff() const
{
    return m_difficulty;
}

inline void ScreenLink::setnbFiles(unsigned int nbFile) {
    m_nbFile = nbFile;
}

inline unsigned int ScreenLink::getNbFiles() const
{
    return m_nbFile;
}

inline GameMode ScreenLink::getMode() const{return m_modeChoose;};
#endif // ScreenLink_H
