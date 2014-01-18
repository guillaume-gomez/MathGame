#ifndef ENEMYMODEL_H
#define ENEMYMODEL_H

#include <sstream>

#include "CharacterModel.hpp"


class EnemyModel : public CharacterModel
{
    public:
        EnemyModel(bool life = true , sf::Vector2f coord = sf::Vector2f(0.0f, 0.0f), float speed = 6.0f, MoveType moveType = NoSliding, unsigned int _nb = 4);
        EnemyModel(const EnemyModel& copy);
        virtual ~EnemyModel();
        void decrementAttempt();
        unsigned int getNbAttempt() const;
        std::string getNbAttemptStr() const;
        bool isActive()const;
        void handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
        void setNbAttempt(unsigned int i);
    protected:
        bool m_isActive;
        // nb attempt (different curves) before IA Activation
        unsigned int m_nbAttempt;
};

inline void EnemyModel::setNbAttempt(unsigned int i)
{
    m_nbAttempt = i;
}

#endif // ENEMYMODEL

