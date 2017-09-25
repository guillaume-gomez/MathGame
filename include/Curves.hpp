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

#ifndef Curves_H
#define Curves_H

#include <stdexcept>
#include <sstream>

#include "../constants.hpp"
#include "EditorObject.hpp"
#include "ConstrueFunction.hpp"
#include "GraphView.hpp"


/// for the moment, Curves can be represented by the multi shaping method
class Curves : public EditorObject
{
public:
    Curves(std::string function = "0", float _begin = 0.0f, float _end = 0.1f, float step = Step);
    virtual ~Curves();
    Curves(const Curves& other);
    virtual EditorObject* clone() const ;
    virtual std::string save(float scale = GraphScale) const ;
    virtual void draw(sf::RenderTarget& app);
    void build(int _begin = - MaxSizeGraph, int _end = MaxSizeGraph, float step = Step);
    std::string getFunction() const;
    const ConstrueFunction* getModel();
    void move(float step = Step);
    void setFunction(std::string str);
    void reset();
    void represent(float step);
    void receiveView(const sf::View view);
    virtual void setColor (const sf::Color& graphColor);
    void drawInterval(sf::RenderTarget& app);

private:
    virtual void setPosition(sf::Vector2f& position);
    virtual void setPosition(float x, float y);
    virtual sf::FloatRect get_GlobalBounds() const ;
    virtual sf::Vector2f get_Position() const;
    virtual EditorObject* loadView(const Element& elmt, float scale);


    ConstrueFunction m_model;
    GraphView m_view;
};

inline EditorObject* Curves::loadView(const Element& elmt, float scale)
{
#ifdef DEBUG
    std::cerr << "nothing to do for the moment";
#endif
    return nullptr;
}

inline void Curves::setPosition(sf::Vector2f& position)
{
    std::runtime_error("In the class Curves::setPosition -> nothing to do");
}


inline void Curves::setPosition(float x, float y)
{
    std::runtime_error("In the class Curves::setPosition -> nothing to do");
}


inline sf::FloatRect Curves::get_GlobalBounds() const
{
    std::runtime_error("In the class Curves::get_GlobalBounds -> nothing to do");
    return sf::FloatRect();
}

inline sf::Vector2f Curves::get_Position() const
{
    std::runtime_error("In the class Curves::get_Position -> nothing to do");
    return sf::Vector2f();
}

inline std::string Curves::getFunction() const
{
    return m_model.getFunction();
}

inline void Curves::setFunction(std::string str)
{
    m_model.setFunction(str);
}

inline void Curves::receiveView(const sf::View view)
{
    m_view.receiveView(view);
}

inline void Curves::setColor(const sf::Color& graphColor)
{
    m_view.setGraphColor(graphColor);
}

#endif // Curves_H
