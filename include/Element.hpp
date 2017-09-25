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

#ifndef Element_H
#define Element_H

struct Element
{
private:
    sf::Vector2f coord;
    TypeObject type;
    float radius;
    bool sens;
    unsigned int nb_attempt;
    std::string function;
    std::string message;
    float begin;
    float end;

public:
    Element();
    inline Element& setCoord(sf::Vector2f v)
    {
        coord = v;
        return (*this);
    }
    inline Element& setType(TypeObject v)
    {
        type = v;
        return (*this);
    }
    inline Element& setRadius(float r)
    {
        radius = r;
        return (*this);
    }
    inline void setSens(bool _s)
    {
        sens = _s;
    }
    inline void setAttempt(unsigned int i)
    {
        nb_attempt = i;
    }
    inline void setEnd(float _end)
    {
        end = _end;
    }
    inline void setBegin(float _begin)
    {
        begin = _begin;
    }
    inline void setFunction(std::string f)
    {
        function = f;
    }
    inline void setMessage(std::string m)
    {
        message = m;
    }
    Element& setType(std::string v);
    inline bool getSens() const
    {
        return sens;
    }
    inline unsigned int getAttempt() const
    {
        return nb_attempt;
    }
    inline sf::Vector2f getCoord() const
    {
        return coord;
    }
    inline TypeObject getType() const
    {
        return type;
    }
    inline float getRadius() const
    {
        return radius;
    }
    inline std::string getFunction() const
    {
        return function;
    }
    inline float getBegin() const
    {
        return begin;
    }
    inline float getEnd() const
    {
        return end;
    }
    inline std::string getMessage()const
    {
        return message;
    }
};

#endif // Element_H
