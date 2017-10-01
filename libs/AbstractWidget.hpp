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

#ifndef ABSTRACTWIDGET_H
#define ABSTRACTWIDGET_H

#include <SFML/Graphics.hpp>
#include "ScopedPtr.hpp"
#include "AbstractWidgetEvent.hpp"

class AbstractPanel;

class AbstractWidget
{
    AbstractWidget	* previous;
    AbstractWidget	* next;
    AbstractWidget	* left;
    AbstractWidget	* right;

    ScopedPtr<AbstractWidgetEvent> use_event;
    ScopedPtr<AbstractWidgetEvent> switch_left_event;
    ScopedPtr<AbstractWidgetEvent> switch_right_event;

    AbstractPanel	* next_panel;
    bool			panel_exit;

protected:
    virtual void OnMove() {}
    virtual void OnUse(bool success) {}
    virtual void OnSwitchLeft(bool success) {}
    virtual void OnSwitchRight(bool success) {}
    virtual void OnGainedFocus() {}
    virtual void OnLostFocus() {}
public:
    // Constructeurs
    AbstractWidget();

    // Destructeur
    virtual ~AbstractWidget() {}

    // Accesseurs
    AbstractWidget * GetPreviousWidget() const;
    AbstractWidget * GetNextWidget() const;
    AbstractWidget * GetLeftWidget() const;
    AbstractWidget * GetRightWidget() const;
    AbstractPanel * GetNextPanel() const;
    bool IsPanelExit() const;
    bool IsSwitchLeftEvent() const;
    bool IsSwitchRightEvent() const;
    bool IsUseEvent() const;

    // Modificateurs de l'objet
    void SetPreviousWidget(AbstractWidget * previous);
    void SetNextWidget(AbstractWidget * next);
    void SetLeftWidget(AbstractWidget * left);
    void SetRightWidget(AbstractWidget * right);
    void SetUseEvent(AbstractWidgetEvent * use_event);
    void SetSwitchLeftEvent(AbstractWidgetEvent * switch_left_event);
    void SetSwitchRightEvent(AbstractWidgetEvent * switch_right_event);
    void SetNextPanel(AbstractPanel * next_panel);
    void SetPanelExit(bool panel_exit);


    // Fonctions de la classe
    bool Use();
    bool SwitchLeft();
    bool SwitchRight();
    void GainFocus();
    void LoseFocus();

    virtual void Calculate(float time_interval) = 0;
    virtual void Draw(sf::RenderTarget & target, float alpha = 1.f) = 0;
};

#endif // ABSTRACTWIDGET_H
