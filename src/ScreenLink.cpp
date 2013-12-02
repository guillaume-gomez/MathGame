#include "ScreenLink.hpp"

ScreenLink::ScreenLink()
:m_filename(FilenameScreenLink), m_countEasy(valEasy), m_countNormal(valNormal), m_countHard(valHard),
 m_maxEasy(1), m_maxNormal(1), m_maxHard(1), m_currentLevel(1), m_difficulty( Normal)
{
    load();
}

void ScreenLink::load()
{
    std::ifstream file(m_filename.c_str());

    if(file.is_open())
    {
        //nbeasy
        std::string dump;
        file >> dump;
        file >> m_countEasy;
        //nbnormal
        file >> dump;
        file >> m_countNormal;
        //nbhard
        file >> dump;
        file >> m_countHard;
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

}

void ScreenLink::save()
{
    std::ofstream  file(m_filename.c_str());

    if(file.is_open())
    {
        file << "countEasy\n";
        //nbeasy
        file << m_countEasy;
        file << "countNormal\n";
        //nbnormal
        file << m_countNormal;
        file << "countHard\n";
        //nbhard
        file << m_countHard;
        file << "maxEasy\n";
        //currentEasy
        file << m_maxEasy;
        file << "maxNormal\n";
        //currentNormal
        file << m_maxNormal;
        file << "maxHard\n";
        //currentHard
        file << m_maxHard;
    }
    else
    {
        file.close();
    }

    file.close();
}

std::ostream& operator<<( std::ostream &flux, const ScreenLink&  stat )
{
        flux << "countEasy : " << stat.m_countEasy << std::endl;
        flux << "countNormal: " << stat.m_countNormal << std::endl;
        flux << "countHard: " <<stat.m_countHard << std::endl;
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
       m_maxEasy = val;
    break;
   case Normal:
       m_maxNormal = val;
    break;
   case Hard:
       m_maxHard = val;
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
