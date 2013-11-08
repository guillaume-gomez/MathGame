#include "LineSFML2_0.hpp"

LineSFML2_0::LineSFML2_0(const sf::Vector2f& startCoords, const sf::Vector2f& endCoords)
:m_startCoords(startCoords), m_endCoords(endCoords)
{
    compute();
    setThickness(1);
}
LineSFML2_0::~LineSFML2_0()
{

}
LineSFML2_0::LineSFML2_0(const LineSFML2_0& other)
{

}
LineSFML2_0& LineSFML2_0::operator=(const LineSFML2_0& other)
{
    m_startCoords=other.m_startCoords;
    m_endCoords=other.m_endCoords;
    m_length=other.m_length;
    m_thickness=other.m_thickness;

    return *this;
}

void LineSFML2_0::compute()
{

}
