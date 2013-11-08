#ifndef Statistics_H
#define Statistics_H

#include <iostream>
#include <fstream>
#include "../files.hpp"
#include "../constants.hpp"

/* temporaire */
const int valEasy = 3 ;
const int valNormal = 3;
const int valHard = 1;

class Statistics
{
    public:
        Statistics();
        virtual ~Statistics();
        void countNbFiles();
        void load();
        void save();
        friend std::ostream& operator<<( std::ostream &flux, const Statistics&  stat );
        void setMaxLevel(Difficulty type , unsigned int val );
        unsigned int getMaxLevel(Difficulty type)const;
        unsigned int getnbEasy() const ;
        unsigned int getnbNormal() const ;
        unsigned int getnbHard() const ;
        void setParamLevel( Difficulty _diff, unsigned int level);
        unsigned int getCurrentLevel()const;
        Difficulty getDiff()const;
        unsigned int getNbFiles()const;

    private:
        std::string m_filename;
        unsigned int m_countEasy;
        unsigned int m_countNormal;
        unsigned int m_countHard;

        unsigned int m_maxEasy;
        unsigned int m_maxNormal;
        unsigned int m_maxHard;

        unsigned int m_currentLevel;
        Difficulty m_difficulty;
};

inline unsigned int Statistics::getnbEasy() const
{
    return m_countEasy;
}

inline unsigned int Statistics::getnbNormal() const
{
    return m_countNormal;
}

inline unsigned int Statistics::getnbHard() const
{
   return m_countHard;
}

inline void Statistics::setParamLevel( Difficulty _diff, unsigned int level)
{
    m_difficulty = _diff;
    m_currentLevel = level;
}

inline unsigned int Statistics::getCurrentLevel()const
{
    return m_currentLevel;
}

inline Difficulty Statistics::getDiff()const
{
    return m_difficulty;
}

inline unsigned int Statistics::getNbFiles()const
{
    //it could be m_countEasy or m_countHard
    //bad architecture :(
    return m_countNormal;
}
#endif // Statistics_H
