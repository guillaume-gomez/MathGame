#include "LineSFML2_1.hpp"

LineSFML2_1::LineSFML2_1(const sf::Vector2f& startCoords, const sf::Vector2f& endCoords)
:m_startCoords(startCoords), m_endCoords(endCoords)
{
    compute();
    setThickness(1);
}
LineSFML2_1::~LineSFML2_1()
{

}
LineSFML2_1::LineSFML2_1(const LineSFML2_1& other)
{
    m_startCoords=other.m_startCoords;
    m_endCoords=other.m_endCoords;
    m_length=other.m_length;
    m_thickness=other.m_thickness;
}
LineSFML2_1& LineSFML2_1::operator=(const LineSFML2_1& other)
{
    m_startCoords=other.m_startCoords;
    m_endCoords=other.m_endCoords;
    m_length=other.m_length;
    m_thickness=other.m_thickness;

    return *this;
}

void LineSFML2_1::compute()
{
    m_length = sqrt(pow(m_endCoords.x-m_startCoords.x,2)+pow(m_endCoords.y-m_startCoords.y,2));
    #ifdef DEBUG
//        // // std::cout << "m_length : " << m_length << std::endl;
    #endif // DEBUG
    setSize(sf::Vector2f(getLength(),getThickness()));
    setPosition(getStartCoords());
    setRotation(atan2(m_endCoords.y-m_startCoords.y, m_endCoords.x-m_startCoords.x)*180/M_PI);
}
