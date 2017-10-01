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

#ifndef SCOPEDPTR_H_INCLUDED
#define SCOPEDPTR_H_INCLUDED

template <class T>
class ScopedPtr
{
    T*   m_ptr;

    ScopedPtr(const ScopedPtr &);
    ScopedPtr & operator=(const ScopedPtr &);
public:
    ScopedPtr() : m_ptr(0) {}
    ScopedPtr(T* ptr) : m_ptr(ptr) {}

    ~ScopedPtr()
    {
        delete m_ptr;
    }

    T & operator * ()
    {
        return *m_ptr;
    }
    T * operator ->()
    {
        return m_ptr;
    }
    operator T*() const
    {
        return m_ptr;
    }

    void reset(T * ptr)
    {
        if(m_ptr != 0)
            delete m_ptr;
        m_ptr = ptr;
    }

    T * get() const
    {
        return m_ptr;
    }
};


#endif // SCOPEDPTR_H_INCLUDED
