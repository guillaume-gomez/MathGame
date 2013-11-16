#include "LevelModel.hpp"

LevelModel::LevelModel()
{
}

LevelModel::LevelModel(std::string _filename , GameMode mode )
:  m_nbPoints(0),m_win(false),m_lose(false),m_nbAttempt(0),m_mode(mode)
{
    m_fileLevel.open(_filename.c_str());
    if ( m_fileLevel.is_open() )
    {
        std::cout << " file :'" << _filename.c_str() <<"'"<< std::endl;
        m_fileLevel >> m_nbPoints;
        m_pointsCheck.clear();
        m_pointsCheck.resize(m_nbPoints);

        m_fileLevel >> m_nbAttempt;
        m_saveNbAttemp = m_nbAttempt;

        if ( m_mode != Classic)
        {
            m_nbAttempt = m_saveNbAttemp = 1;
        }

        for ( unsigned int i = 0 ; i < m_nbPoints ; i++)
        {
            m_pointsCheck[i] = false;
            //
            sf::Vector2f temp;
            m_fileLevel >> temp.x;
            m_fileLevel >> temp.y;

            m_coordPoints.push_back(temp);
        }
    }
    else
    {

        std::cerr << "Error file :'" << _filename.c_str() << "' cannot exist" << std::endl;
        m_fileLevel.close();
    }

    m_fileLevel.close();
}

std::ostream& operator<<( std::ostream &flux,const LevelModel& level )
{
     flux << level.m_nbPoints  << std::endl;

     for (unsigned int i = 0 ; i < level.m_nbPoints ; i++)
     {
         flux << "Point "<< i << ": x = " << level.m_coordPoints[i].x << " y = " << level.m_coordPoints[i].y << std::endl;
     }
     return flux;
}


/**
**
**/
void LevelModel::IsFinishing ( CharacterModel& charactermodel ,float _scale , bool& playableSound)
{
    playableSound = false;
    sf::FloatRect position_and_Size = charactermodel.getRect();

                  position_and_Size.width /= _scale;
                  position_and_Size.height /= _scale;

                  position_and_Size.left -= position_and_Size.width/2;

    for ( unsigned int i = 0 ; i < getNbPoints()-1 ; i++)
    {
        //test the colissions and if the colission already done between the point and the chracter
        if ( !m_pointsCheck[i] && position_and_Size.contains( m_coordPoints[i] ) )
        {
             m_pointsCheck[i] = true;
             playableSound = true;
        }
    }

    //to avoid the sound
    if ( position_and_Size.contains( m_coordPoints[ getNbPoints() - 1 ] ) )
        {
             m_pointsCheck[ getNbPoints() - 1 ] = true;
             playableSound = false;
        }

 m_win = true;
    for ( unsigned int i = 0 ; i < getNbPoints() ; i++)
    {
       if ( m_pointsCheck[i] == false)
       {
           m_win = false;
       }
    }
    if ( !m_win && m_pointsCheck[ getNbPoints() - 1])
    {
        m_pointsCheck[ getNbPoints() - 1] = false;
    }
}

void LevelModel::IsLosing()
{
    if ( m_nbAttempt < 0)
    {
        m_lose = true;
    }
}

void LevelModel::reset()
{
    m_lose = false;
    m_win = false;

    for ( unsigned int i = 0 ; i < m_pointsCheck.size() ; i++)
    {
        m_pointsCheck[i] = false;
    }
    m_nbAttempt = m_saveNbAttemp;


}

LevelModel::~LevelModel()
{
    //dtor
}
