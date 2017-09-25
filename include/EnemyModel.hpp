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
    // nb attempt (different curves) before IA Activation
    unsigned int m_nbAttempt;
    bool m_isActive;
};

inline void EnemyModel::setNbAttempt(unsigned int i)
{
    m_nbAttempt = i;
    m_isActive = i==0;
}


#endif // ENEMYMODEL

