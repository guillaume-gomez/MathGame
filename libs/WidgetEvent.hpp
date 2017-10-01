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

#ifndef WIDGETEVENT_H_INCLUDED
#define WIDGETEVENT_H_INCLUDED

class BoolSwapWidgetEvent : public AbstractWidgetEvent
{
    bool & m_value;
public:
    BoolSwapWidgetEvent(bool & value) : m_value(value) {}
    virtual bool Execute()
    {
        m_value = !m_value;
        return true;	// Renvoyer true si l'opération s'est bien passée, false en cas contraire.
    }
};

#endif // WIDGETEVENT_H_INCLUDED
