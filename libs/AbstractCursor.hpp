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

#ifndef ABSTRACTCURSOR_H
#define ABSTRACTCURSOR_H

#include <SFML/Graphics.hpp>

class AbstractWidget;
class AbstractPanel;

class AbstractCursor
{
    AbstractWidget * previous;
    AbstractWidget * current;

protected:
    virtual void OnMoveNext(bool success) {}
    virtual void OnMovePrevious(bool success) {}
    virtual void OnMoveLeft(bool success) {}
    virtual void OnMoveRight(bool success) {}
    virtual void OnMoveExit(bool success) {}
    virtual void OnSwitchLeft(bool success) {}
    virtual void OnSwitchRight(bool success) {}

    virtual void OnUse(bool success) {}
    virtual void OnInit() {}
public:
    // Constructeurs
    AbstractCursor(AbstractWidget * first = 0);

    // Destructeur
    virtual ~AbstractCursor() {}

    // Accesseurs
    AbstractWidget * GetPrevious() const;
    AbstractWidget * GetCurrent() const;
    AbstractPanel * GetNextPanel() const;
    bool IsPanelExit() const;

    // Modificateurs de l'objet
    void InitWidget(AbstractWidget * widget);
    void GoToWidget(AbstractWidget * widget);

    // Fonctions de la classe
    void Next();
    void Previous();
    void Left();
    void Right();
    void Use();
    void Exit();

    virtual void Calculate(float time_interval) = 0;
    virtual void Draw(sf::RenderTarget & target, float alpha = 1.f) = 0;
};

#endif // ABSTRACTCURSOR_H
