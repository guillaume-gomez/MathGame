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

#ifndef AXIS_HPP
#define AXIS_HPP

class Axis
{
public:
    Axis(float graduation = 5.0f);
    virtual ~Axis();
    int getxAxis();
    int getyAxis();
    float getScale();
    void setGraduation( float _graduation);
    float getGraducation();

    void draw(sf::RenderWindow& App);
    void receiveView(const sf::View view);

private:
    int m_originyAxis;
    int m_originxAxis;
    float m_scale;
    float m_graduation;
    sf::VertexArray m_listAxis;
    std::vector<sf::RectangleShape> m_listXGrad;
    std::vector<sf::RectangleShape> m_listYGrad;
    sf::RectangleShape m_shapexAxis;
    sf::RectangleShape m_shapeyAxis;

    sf::View m_view;


};


inline void Axis::receiveView(const sf::View view)
{
    m_view = view;
}
#endif // AXIS_HPP
