
#include "EnemyModel.hpp"

EnemyModel::EnemyModel(bool life, sf::Vector2f coord, float speed, MoveType moveType, unsigned int _nbActive)
:CharacterModel(life,coord,speed,moveType), m_nbAttempt(_nbActive),m_isActive(false)
{
    if(m_nbAttempt == 0)
    {
    	m_isActive = true;
    }

    //temporaire
    m_nbAttempt = 3;
}

EnemyModel::EnemyModel(const EnemyModel& copy)
:CharacterModel(copy.m_life, copy.getCoords(), copy.m_speed, copy.m_moveType),
 m_nbAttempt(copy.m_nbAttempt), m_isActive(copy.m_isActive)
{
    if(m_nbAttempt == 0)
    {
        m_isActive = true;
    }
}

EnemyModel::~EnemyModel()
{
    //dtor
}

 void EnemyModel::handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction)
 {
    if(isActive())
    {
        CharacterModel::handle_input(event,textAreaFunction);
    }
    if(isActive())
    {
        float speed = 0;
        if(m_orientedRight)
        {
            speed = m_speed;
        }
        else
        {
            speed = - m_speed;
        }
        m_PhysicsBox.setThrust(sf::Vector2f(speed, m_PhysicsBox.getThrust().y));
    }
 }


void EnemyModel::decrementAttempt()
{
    if(m_nbAttempt > 0)
    {
        m_nbAttempt--;
        if(m_nbAttempt == 0)
        {
            m_isActive = true;
        }
    }
}


 bool EnemyModel::isActive()const {return m_isActive;}

 unsigned int EnemyModel::getNbAttempt() const { return m_nbAttempt;}


std::string EnemyModel::getNbAttemptStr() const
{
    std::ostringstream oss;
    //std::cout << "EnemyModel::getNbAttemptStr"<< m_nbAttempt << std::endl;
    oss << getNbAttempt();
    return oss.str();
}
