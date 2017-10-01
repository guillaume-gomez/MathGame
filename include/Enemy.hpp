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

#ifndef ENEMY_H
#define ENEMY_H

#include "EditorObject.hpp"
#include "EnemyModel.hpp"
#include "EnemyView.hpp"

class Enemy : public EditorObject
{
public:
    Enemy();
    Enemy(const Enemy& copy);
    virtual ~Enemy();
    virtual const EnemyModel& getModel() const;
    virtual const EnemyView& getView();
    virtual void handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
    virtual void show();
    virtual void draw(sf::RenderTarget& app);
    virtual void reset();
    void setMoveType(CharacterModel::MoveType moveType);
    void setDirection(bool _dir);
    void setFrictionCoefficient(float frictionCoefficient);
    void setTexture(const sf::Texture* texture, int frameWidth, int frameHeight);
    void playSound();
    void decrementAttempt();
    void setNbAttempt(unsigned int i);
    unsigned int getNbAttempt() const;
    virtual sf::Vector2f get_Position() const;
    virtual void setPosition(sf::Vector2f& pos);
    virtual void setPosition(float x, float y);
    virtual sf::FloatRect get_GlobalBounds() const;
    virtual EditorObject* clone() const;
    virtual std::string save(float scale = GraphScale) const;
    virtual EditorObject* loadView(const Element& elmt, float scale);
    void addToEngine();
private:
    EnemyModel m_model;
    EnemyView m_view;
};


inline const EnemyModel& Enemy::getModel() const
{
    return m_model;
}

inline const EnemyView& Enemy::getView()
{
    return m_view;
}

inline unsigned int Enemy::getNbAttempt() const
{
    return m_model.getNbAttempt();
}

inline void Enemy::decrementAttempt()
{
    m_model.decrementAttempt();
}

inline void Enemy::setNbAttempt(unsigned int value)
{
    m_model.setNbAttempt(value);
}
//
// had to be used only for the editor, during the game, the model define it position
//
inline void Enemy::setPosition(sf::Vector2f& pos)
{
    m_model.setCoords(pos);
};
inline void Enemy::setPosition(float x, float y)
{
    m_model.setCoords(x,y);
};

inline sf::Vector2f Enemy::get_Position() const
{
    return m_model.getCoords();
};

inline sf::FloatRect Enemy::get_GlobalBounds() const
{
    return m_view.getGlobalBounds();
};

inline void Enemy::addToEngine()
{
    m_model.addToEngine();
}

#endif // ENEMY_H
