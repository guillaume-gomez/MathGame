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

struct Element
{
    private:
        sf::Vector2f coord;
        TypeObject type;
        float radius;
        bool sens;
        unsigned int nb_attempt;

    public:
        Element();
        inline bool getSens() const { return sens;}
        inline unsigned int getAttempt() const { return nb_attempt;}
        inline Element& setCoord(sf::Vector2f v) {coord = v;return (*this);}
        inline Element& setType(TypeObject v) {type = v;return (*this);}
        inline Element& setRadius(float r){radius = r; return (*this);}
        inline void setSens(bool _s) { sens = _s;}
        inline void setAttempt(unsigned int i){ nb_attempt = i;}
        Element& setType(std::string v);
        inline sf::Vector2f getCoord() const {return coord;}
        inline TypeObject getType() const {return type;}
        inline float getRadius() const {return radius;}
};

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
        void decrementAttempt();
        void reset();
        int getSaveAttempt()const;
        void setMode(GameMode _mode);
        GameMode getMode() const;


    private:
        LevelModel();
        std::vector<Element> m_coordElements;
        std::ifstream m_fileLevel;
        bool m_lose;
        int m_nbAttempt;
        unsigned int m_nbElements;
        GameMode m_mode;
        std::vector<bool> m_pointsCheck;
        int m_saveNbAttemp;
        bool m_win;
};

/******************************************************************************
*                     Accessors
*******************************************************************************/
inline bool LevelModel::isWin() const {return m_win;};

inline bool LevelModel::IsLose() const {return m_lose;};

inline unsigned int LevelModel::getNbPoints() const {return m_nbElements;};


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


inline bool LevelModel::getCheckValue(unsigned int i)const
{
    if (i < m_pointsCheck.size())
    {
            return m_pointsCheck[i];
    }
    return false;
}

inline unsigned int LevelModel::getNbAttempt() const {return m_nbAttempt;};

inline void LevelModel::decrementAttempt() {m_nbAttempt--;};

inline int LevelModel::getSaveAttempt() const {return m_saveNbAttemp;};

inline void LevelModel::setMode(GameMode _mode) {m_mode = _mode;};

inline GameMode LevelModel::getMode() const {return  m_mode;};

/******************************************************************************
*                     Accessors
*******************************************************************************/
#endif // LEVELMODEL_H
