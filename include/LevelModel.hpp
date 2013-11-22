#ifndef LEVELMODEL_H
#define LEVELMODEL_H

#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>

#include "../constants.hpp"
#include "CharacterModel.hpp"

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
        sf::Vector2f getCoordPoints( unsigned int i) const ;
        void IsFinishing ( CharacterModel& charactermodel,float _scale , bool& playableSound);
        bool getCheckValue( unsigned int i )const;
        void IsLosing();
        friend std::ostream& operator<<( std::ostream &flux, const LevelModel&  level );
        int getNbAttempt()const;
        void decrementAttempt();
        void reset();
        int getSaveAttempt()const;
        void setMode(GameMode _mode);
        GameMode getMode() const;


    private:
        LevelModel();
        std::ifstream m_fileLevel;
        unsigned int m_nbPoints;
        std::vector<sf::Vector2f> m_coordPoints;
        std::vector<bool> m_pointsCheck;
        bool m_win;
        bool m_lose;
        int m_nbAttempt;
        int m_saveNbAttemp;
        GameMode m_mode;



};

/******************************************************************************
*                     Accessors
*******************************************************************************/
inline bool LevelModel::isWin() const { return m_win;};

inline bool LevelModel::IsLose() const { return m_lose;};

inline unsigned int LevelModel::getNbPoints() const { return m_nbPoints;};

inline sf::Vector2f LevelModel::getCoordPoints( unsigned int i) const
{
    if ( i < m_coordPoints.size() )
    {
        return m_coordPoints[ i ];
    }
    return sf::Vector2f(-1.0f,-1.0f);
};

inline sf::Vector2f LevelModel::getGoalCoord()const { if(m_coordPoints.size() > 0 )return m_coordPoints[ m_coordPoints.size() - 1];else sf::Vector2f(0.0f,0.0f);};

inline bool LevelModel::getCheckValue( unsigned int i )const
{
    if ( i < m_pointsCheck.size())
    {
            return m_pointsCheck[i];
    }
    return false;
}

inline  int LevelModel::getNbAttempt()const { return m_nbAttempt;};

inline void LevelModel::decrementAttempt(){ m_nbAttempt--;};

inline int LevelModel::getSaveAttempt()const {return m_saveNbAttemp;};

inline void LevelModel::setMode(GameMode _mode){m_mode = _mode;};

inline GameMode LevelModel::getMode() const { return  m_mode;};

/******************************************************************************
*                     Accessors
*******************************************************************************/



#endif // LEVELMODEL_H
