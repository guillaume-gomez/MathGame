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

#include <stdexcept>

#include "LevelModel.hpp"


///an element does not contain always a radius (example, an ennemy)
Element::Element()
: radius(-1.0f)
{

}

LevelModel::LevelModel()
{
}

LevelModel::LevelModel(std::string _filename , GameMode mode )
:m_beginPoint(0), m_nbElements(0), m_win(false), m_lose(false), m_nbAttempt(0), m_mode(mode), m_initialPosition(sf::Vector2f(0.0f, 0.0f))
{
    m_fileLevel.open(_filename.c_str());
    if(m_fileLevel.is_open())
    {
//        // std::cout << " file :'" << _filename.c_str() <<"'"<< std::endl;
        m_fileLevel >> m_nbElements;
        m_pointsCheck.clear();
        m_pointsCheck.resize(m_nbElements);

        m_fileLevel >> m_nbAttempt;
        m_saveNbAttemp = m_nbAttempt;

        if(m_mode == GameMode::NoChance)
        {
            m_nbAttempt = m_saveNbAttemp = 1;
        }

        if(m_mode == GameMode::Classic)
        {
            if(m_nbAttempt > 2)m_nbAttempt--;
            m_saveNbAttemp = m_nbAttempt;
        }


        for( unsigned int i = 0 ; i < m_nbElements ; i++)
        {
            m_pointsCheck[i] = false;
            //
            std::string type;
            m_fileLevel >> type;
            Element newElmt;
            if(type == CircleStr)
            {
                float radius;
                m_fileLevel >> radius;
                newElmt.setRadius(radius);
                newElmt.setType(TypeObject::Circle);
                sf::Vector2f temp;
                m_fileLevel >> temp.x;
                m_fileLevel >> temp.y;
                newElmt.setCoord(temp);

                //because it is not a point
                m_pointsCheck[i] = true;
            }
            else if (type == PointStr)
            {
                newElmt.setType(TypeObject::Point);
                sf::Vector2f temp;
                m_fileLevel >> temp.x;
                m_fileLevel >> temp.y;
                newElmt.setCoord(temp);

            }
            else if (type == GoalPointStr)
            {
                newElmt.setType(TypeObject::GoalPoint);
                sf::Vector2f temp;
                m_fileLevel >> temp.x;
                m_fileLevel >> temp.y;
                newElmt.setCoord(temp);

            }
            else if (type == EnemyStr)
            {
                unsigned int nbAttempt;
                bool direction;
                m_fileLevel >> nbAttempt;
                m_fileLevel >> direction;

                newElmt.setType(TypeObject::Enemy);
                newElmt.setAttempt(nbAttempt);
                newElmt.setSens(direction);

                sf::Vector2f temp;
                m_fileLevel >> temp.x;
                m_fileLevel >> temp.y;
                newElmt.setCoord(temp);

                 //because it is not a point
                m_pointsCheck[i] = true;
            }
            else if(type == IntegralStr)
            {
                std::string function;
                float min, max;
                m_fileLevel >> function;
                m_fileLevel >> min;
                m_fileLevel >> max;

                newElmt.setType(TypeObject::Integral);
                newElmt.setFunction(function);
                newElmt.setBegin(min);
                newElmt.setEnd(max);

                 //because it is not a point
                m_pointsCheck[i] = true;

            }
            else if(type == FunctionStr)
            {
                std::string function;
                m_fileLevel >> function;

//                #ifdef DEBUG
//                    std::cout << "LevelModel::LevelModel if(type == FunctionStr) function : " << function << std::endl;
//                #endif // DEBUG
                newElmt.setType(TypeObject::Function);
                newElmt.setFunction(function);
                 //because it is not a point
                m_pointsCheck[i] = true;
            }
            else if (type == InfoStr)
            {
                newElmt.setType(TypeObject::Info);
                sf::Vector2f temp;
                m_fileLevel >> temp.x;
                m_fileLevel >> temp.y;
                newElmt.setCoord(temp);

                //very very dirty.....but it works :)
                std::string content;
                m_fileLevel.clear();
                m_fileLevel.ignore(INTMAX_MAX,'\n');
                getline(m_fileLevel, content, '#');
                m_fileLevel.clear();
                m_fileLevel.ignore(INTMAX_MAX,'\n');

                newElmt.setMessage(content);

                 //because it is not a point
                m_pointsCheck[i] = true;
            }
            else if(type == HeroInitialPosition) {
                m_fileLevel >> m_initialPosition.x >> m_initialPosition.y;
            }

            m_coordElements.push_back(newElmt);
        }
    }
    else
    {
        #ifdef DEBUG
            std::cerr << "Error file :'" << _filename.c_str() << "' cannot exist" << std::endl;
        #endif
        std::runtime_error("Cannot load the file level\n");
        m_fileLevel.close();
    }

    m_fileLevel.close();
}

std::ostream& operator<<( std::ostream &flux, const LevelModel& level )
{
     flux << level.m_nbElements << std::endl;
     for(unsigned int i = 0 ; i < level.m_nbElements ; i++)
     {
         flux << "Elements  ("<< i <<") "<< ": x = " << level.m_coordElements[i].getCoord().x << " y = " << level.m_coordElements[i].getCoord().y << std::endl;
     }
     return flux;
}


/**
**
**/
void LevelModel::IsFinishing ( const CharacterModel& charactermodel ,float _scale , bool& playableSound)
{
    playableSound = false;
    sf::FloatRect position_and_Size = charactermodel.getRect();

                  position_and_Size.width /= _scale;
                  position_and_Size.height /= _scale;

                  position_and_Size.left -= position_and_Size.width / 2;

    for(unsigned int i = 0 ; i < getNbPoints()-1 ; i++)
    {
        //check the colissions and if the colission had already done between the point and the chracter
        if(!m_pointsCheck[i] && position_and_Size.contains( m_coordElements[i].getCoord() ) )
        {
            #ifdef DEBUG
             //std::cout << "Colliding index " << i << std::endl;
            #endif
            m_pointsCheck[i] = true;
            playableSound = true;
        }
    }

    //to avoid the sound
    if(position_and_Size.contains( m_coordElements[ getNbPoints() - 1 ].getCoord() ) )
    {
             m_pointsCheck[ getNbPoints() - 1 ] = true;
             playableSound = false;
    }

    m_win = true;
    for(unsigned int i = 0 ; i < getNbPoints() ; i++)
    {
       if(m_pointsCheck[i] == false)
       {
           m_win = false;
       }
    }
    if(!m_win && m_pointsCheck[ getNbPoints() - 1])
    {
        m_pointsCheck[ getNbPoints() - 1] = false;
    }
}

void LevelModel::IsLosing()
{
    if(m_nbAttempt < 0)
    {
        m_lose = true;
    }
}

void LevelModel::reset()
{
    m_lose = false;
    m_win = false;

    for(unsigned int i = 0 ; i < m_pointsCheck.size() ; i++)
    {
        if( m_coordElements.at(i).getType() == TypeObject::Point ||
            m_coordElements.at(i).getType() == TypeObject::GoalPoint
        )
        {
            m_pointsCheck[i] = false;
        }
    }
    m_nbAttempt = m_saveNbAttemp;


}

std::vector<std::string> LevelModel::getVectorFunctions()
{
    std::vector<std::string> vector;
    for (auto it: m_coordElements)
    {
        if(it.getType() == TypeObject::Function)
        {
            vector.push_back(it.getFunction());
        }
    }
    return vector;
}

LevelModel::~LevelModel()
{
    //dtor
}
