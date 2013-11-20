#ifndef LINESFML2_1_H
#define LINESFML2_1_H

#ifdef DEBUG
	#include <iostream>
#endif

#include <cmath>
#include <SFML/Graphics/RectangleShape.hpp>

class LineSFML2_1 : public sf::RectangleShape
{
    public:
        LineSFML2_1(const sf::Vector2f& startCoords=sf::Vector2f(0,0), const sf::Vector2f& endCoords=sf::Vector2f(0,0));
        virtual ~LineSFML2_1();
        LineSFML2_1(const LineSFML2_1& other);
        LineSFML2_1& operator=(const LineSFML2_1& other);

        void setStartCoords(const sf::Vector2f& startCoords);
        void setEndCoords(const sf::Vector2f& endCoords);
        const sf::Vector2f& getStartCoords() const;
        const sf::Vector2f& getEndCoords() const;

        float getLength() const;
        void setThickness(float thickness);
        float getThickness() const;

    protected:
    private:
        sf::Vector2f m_startCoords, m_endCoords;
        float m_length, m_thickness;

        void compute();

//        void  setSize (const sf::Vector2f &size) ;
//        const sf::Vector2f &  getSize () const  ;
//        void  setOutlineThickness (float thickness) ;
//        float  getOutlineThickness () const;
};

/***************************************** Definitions *****************************************/
/**/
/**/	inline void LineSFML2_1::setStartCoords(const sf::Vector2f& startCoords)
/**/	{
/**/		m_startCoords = startCoords;
/**/		compute();
/**/	}
/**/
/**/	inline void LineSFML2_1::setEndCoords(const sf::Vector2f& endCoords)
/**/	{
/**/		m_endCoords = endCoords;
/**/		compute();
/**/	}
/**/
/**/	inline const sf::Vector2f& LineSFML2_1::getStartCoords() const
/**/	{
/**/		return m_startCoords;
/**/	}
/**/
/**/	inline const sf::Vector2f& LineSFML2_1::getEndCoords() const
/**/	{
/**/		return m_endCoords;
/**/	}
/**/
/**/	inline float LineSFML2_1::getLength() const
/**/	{
/**/		return m_length;
/**/	}
/**/
/**/	inline void LineSFML2_1::setThickness(float thickness)
/**/	{
/**/		m_thickness = thickness;
/**/		sf::RectangleShape::setOrigin(0.0f,m_thickness/2.0f);
/**/		compute();
/**/	}
/**/
/**/	inline float LineSFML2_1::getThickness() const
/**/	{
/**/		return m_thickness;
/**/	}
/**/
/***************************************** // Definitions *****************************************/

#endif // LINESFML2_1_H
