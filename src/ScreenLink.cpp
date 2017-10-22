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

#include "ScreenLink.hpp"

ScreenLink::ScreenLink():
 m_currentLevel(1), m_difficulty(Normal),
 m_maxEasy(1), m_maxNormal(1), m_maxHard(1), m_nbFile(4)
{
    load();
}

void ScreenLink::load()
{
    std::ifstream file(FilenameScreenLink);

    if(file.is_open())
    {
        //nbeasy
        std::string dump;
        //currentEasy
        file >> dump;
        file >> m_maxEasy;
        //currentNormal
        file >> dump;
        file >> m_maxNormal;
        //currentHard
        file >> dump;
        file >> m_maxHard;
    }
    else
    {
        file.close();
    }

    file.close();

    std::ifstream i(FilenameJsonLevels);
    json data;
    i >> data;
    m_nbFile = data["levels"].size();
}

void ScreenLink::save()
{
    std::ofstream  file(FilenameScreenLink);

    if(file.is_open())
    {
        file << "maxEasy\n";
        //currentEasy
        file << m_maxEasy << std::endl;
        file << "maxNormal\n";
        //currentNormal
        file << m_maxNormal << std::endl;
        file << "maxHard\n";
        //currentHard
        file << m_maxHard << std::endl;
    }
    else
    {
        file.close();
    }

    file.close();
}

std::ostream& operator<<( std::ostream &flux, const ScreenLink&  stat )
{
    flux << "maxEasy: " << stat.m_maxEasy << std::endl;
    flux << "maxNormal: "<< stat.m_maxNormal << std::endl;
    flux << "maxHard: " << stat.m_maxHard << std::endl;
    flux << "CurrentLevel: " << stat.m_currentLevel << " difficulty: " << stat.m_difficulty;

    return flux;
}

void ScreenLink::countNbFiles()
{
//TODO
}

ScreenLink::~ScreenLink()
{
    //dtor
}


void ScreenLink::setMaxLevel(Difficulty type , unsigned int val)
{
    switch(type)
    {
   case Easy:
       m_maxEasy = m_maxEasy < val ? val : m_maxEasy;
    break;
   case Normal:
       m_maxNormal = m_maxNormal < val ? val : m_maxNormal;
    break;
   case Hard:
       m_maxHard = m_maxHard < val ? val : m_maxHard;
    break;
    default:
    	#ifdef DEBUG
			std::cerr << "Error : Wrong kind of difficulty" << std::endl;
    	#endif // DEBUG
    break;
    }

}


unsigned int ScreenLink::getMaxLevel(Difficulty type)const
{
    switch(type)
    {
   case Easy:
       return m_maxEasy;
    break;
   case Normal:
       return m_maxNormal;
    break;
   case Hard:
       return m_maxHard;
    break;
    default:
        #ifdef DEBUG
			std::cerr << "Error : Wrong kind of difficulty" << std::endl;
    	#endif // DEBUG
    break;
    }
    return -1;

}
