#ifndef ENEMYMODEL_H
#define ENEMYMODEL_H

#include <sstream>

#include "CharacterModel.hpp"


class EnemyModel : public CharacterModel
{
    public:
        EnemyModel(bool life = true , sf::Vector2f coord = sf::Vector2f(0.0f, 0.0f), float speed = 6.0f, MoveType moveType = NoSliding, unsigned int _nb = 1);
        virtual ~EnemyModel();
        void decrementAttempt();
        unsigned int getNbAttempt() const;
        std::string getNbAttemptStr() const;
        bool isActive()const;
        void setDirection(bool _dir);
        bool getDirection()const;
        void handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
    protected:
        bool m_direction;
        bool m_isActive;
        // nb attempt (different curves) before IA Activation
        unsigned int m_nbAttempt;
};

#endif // ENEMYMODEL

