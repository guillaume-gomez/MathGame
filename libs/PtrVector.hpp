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

#ifndef PTRVECTOR_H_INCLUDED
#define PTRVECTOR_H_INCLUDED

#include <cstdlib>
#include <vector>

template<typename V>
class PtrVector
{
    std::vector<V *> m_vector;

public:
    typedef typename std::vector<V *>::iterator iterator;
    typedef typename std::vector<V *>::const_iterator const_iterator;

    PtrVector() {}

    ~PtrVector()
    {
        for(iterator it = m_vector.begin(); it != m_vector.end(); ++it)
            delete *it;
    }

    void push_back(V * value)
    {
        m_vector.push_back(value);
    }
    V & operator [](size_t id)
    {
        return *m_vector[id];
    }
    size_t size()
    {
        return m_vector.size();
    }
    bool empty()
    {
        return m_vector.empty();
    }
    iterator begin()
    {
        return m_vector.begin();
    }
    iterator end()
    {
        return m_vector.end();
    }
};


#endif // PTRVECTOR_H_INCLUDED
