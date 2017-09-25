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

#ifndef HERO_H
#define HERO_H


#include "CharacterModel.hpp"
#include "CharacterView.hpp"
#include "EditorObject.hpp"

class Hero : public EditorObject
{
public:
    Hero();
    Hero(const Hero& copy);
    virtual ~Hero();
    virtual const CharacterModel& getModel();
    virtual const CharacterView& getView();
    virtual void handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
    virtual void show();
    virtual void draw(sf::RenderTarget& app);
    virtual void reset();
    void setMoveType(CharacterModel::MoveType moveType);
    void setFrictionCoefficient(float frictionCoefficient);
    void setTexture(const sf::Texture* texture, int frameWidth, int frameHeight);
    void playSound();
    inline EditorObject* loadView(const Element& elmt, float scale);

    virtual sf::Vector2f get_Position() const;
    virtual void setPosition(sf::Vector2f& pos);
    virtual void setPosition(float x, float y);
    virtual sf::FloatRect get_GlobalBounds() const;
    virtual EditorObject* clone() const;
    virtual std::string save(float scale = GraphScale) const;
private:
    CharacterModel m_model;
    CharacterView m_view;

};

inline EditorObject* Hero::loadView(const Element& elmt, float scale)
{
#ifdef DEBUG
    std::cerr << "nothing to do for the moment";
#endif
    return this;
}
inline const CharacterModel& Hero::getModel()
{
    return m_model;
}

inline const CharacterView& Hero::getView()
{
    return m_view;
}

inline void Hero::setMoveType(CharacterModel::MoveType moveType)
{
    m_model.setMoveType(moveType);
}

inline void Hero::setFrictionCoefficient(float frictionCoefficient)
{
    m_model.setFrictionCoefficient(frictionCoefficient);
}

inline void Hero::setTexture(const sf::Texture* texture, int frameWidth, int frameHeight)
{
    m_view.setTexture(texture, frameWidth, frameHeight);
}

inline void Hero::playSound()
{
    m_view.m_sound.play();
}


//
// had to be used only for the editor, during the game, the model define it position
//
inline void Hero::setPosition(sf::Vector2f& pos)
{
    m_model.setCoords(pos);
};
inline void Hero::setPosition(float x, float y)
{
    m_model.setCoords(x,y);
};

inline sf::Vector2f Hero::get_Position() const
{
    return m_model.getCoords();
};

inline sf::FloatRect Hero::get_GlobalBounds() const
{
    return m_view.getGlobalBounds();
};


#endif // HERO_H
