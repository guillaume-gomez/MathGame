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

#ifndef MANAGEFUNCTIONS_H
#define MANAGEFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "../constants.hpp"
#include "Curves.hpp"


class ManageFunctions
{
public:
    ManageFunctions();
    virtual ~ManageFunctions();
    void handle_input(sf::Event& event);
    void draw(sf::RenderTarget& app);
    void addFunction(std::string function);
    void represent(float step);
    bool isChanged() const;
    void reset();
    void resetToZero();
    std::string getFunction()const;
    const ConstrueFunction* getModelIndex();
    void setViews(const sf::View view);
    bool drawBefore(sf::RenderTarget& app);
    bool drawAfter(sf::RenderTarget& app);
    bool showAfter();
    bool showBefore();
    bool isEmpty() const;
    void colorize();

private:
    bool m_changed;
    std::vector<Curves>::size_type m_currentIndex;
    std::vector<Curves> m_vectorCurves;
    sf::View m_view;
};


inline bool ManageFunctions::isChanged() const
{
    return m_changed;
}

inline std::string ManageFunctions::getFunction() const
{
    return m_vectorCurves.at(m_currentIndex).getFunction();
}

inline bool ManageFunctions::isEmpty() const
{
    return m_vectorCurves.empty();
}

#endif // MANAGEFUNCTIONS_H
