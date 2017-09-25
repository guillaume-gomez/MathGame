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

#ifndef PTRLIST_H_INCLUDED
#define PTRLIST_H_INCLUDED

#include <list>

template<typename V>
class PtrList
{
    std::list<V *> m_list;

public:
    typedef typename std::list<V *>::iterator iterator;
    typedef typename std::list<V *>::const_iterator const_iterator;

    PtrList() {}

    ~PtrList()
    {
        for(iterator it = m_list.begin(); it != m_list.end(); ++it)
            delete *it;
    }

    void push_back(V * value)
    {
        m_list.push_back(value);
    }
    void push_front(V * value)
    {
        m_list.push_front(value);
    }

    void remove(V * value)
    {
        delete value;
        m_list.remove(value);
    }

    void erase(iterator it)
    {
        delete *it;
        m_list.erase(it);
    }

    size_t size()
    {
        return m_list.size();
    }
    bool empty()
    {
        return m_list.empty();
    }
    iterator begin()
    {
        return m_list.begin();
    }
    iterator end()
    {
        return m_list.end();
    }
};

#endif // PTRLIST_H_INCLUDED
