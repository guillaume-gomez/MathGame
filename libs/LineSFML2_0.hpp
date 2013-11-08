#ifndef LINESFML2_0_H
#define LINESFML2_0_H

#ifdef DEBUG
	#include <iostream>
#endif

#include <cmath>
#include <SFML/Graphics/RectangleShape.hpp>

class LineSFML2_0 : public sf::RectangleShape
{
    public:
        LineSFML2_0(const sf::Vector2f& startCoords=sf::Vector2f(0,0), const sf::Vector2f& endCoords=sf::Vector2f(0,0));
        virtual ~LineSFML2_0();
        LineSFML2_0(const LineSFML2_0& other);
        LineSFML2_0& operator=(const LineSFML2_0& other);

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
/**/	inline void LineSFML2_0::setStartCoords(const sf::Vector2f& startCoords)
/**/	{
/**/		m_startCoords = startCoords;
/**/		compute();
/**/	}
/**/
/**/	inline void LineSFML2_0::setEndCoords(const sf::Vector2f& endCoords)
/**/	{
/**/		m_endCoords = endCoords;
/**/		compute();
/**/	}
/**/
/**/	inline const sf::Vector2f& LineSFML2_0::getStartCoords() const
/**/	{
/**/		return m_startCoords;
/**/	}
/**/
/**/	inline const sf::Vector2f& LineSFML2_0::getEndCoords() const
/**/	{
/**/		return m_endCoords;
/**/	}
/**/
/**/	inline float LineSFML2_0::getLength() const
/**/	{
/**/		return m_length;
/**/	}
/**/
/**/	inline void LineSFML2_0::setThickness(float thickness)
/**/	{
/**/		m_thickness = thickness;
/**/		sf::RectangleShape::setOrigin(0.0f,m_thickness/2.0f);
/**/		compute();
/**/	}
/**/
/**/	inline float LineSFML2_0::getThickness() const
/**/	{
/**/		return m_thickness;
/**/	}
/**/
/***************************************** // Definitions *****************************************/

#endif // LINESFML2_0_H
