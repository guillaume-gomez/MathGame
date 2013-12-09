#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <list>
#include <vector>
#include <limits>

#include <SFML/Graphics.hpp>

#include "ConstrueFunction.hpp"
#include "../libs/LineSFML2_1.hpp"


#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)


class GraphView
{
    public:
        GraphView( ConstrueFonction& model, float thickness = 1.0f, float scale = 1.0f);
        virtual ~GraphView();
        void represent(float step);
        void draw( sf::RenderWindow& App );
        void setGraphColor(const sf::Color& graphColor);

	private:
	    const ConstrueFonction& m_model;
		float m_thickness;
		float m_scale;
        sf::Color m_graphColor;
        std::list<LineSFML2_1> m_lines;
};

/**
*  accessors
**/

inline void GraphView::setGraphColor(const sf::Color& graphColor)
{
	m_graphColor = graphColor;
}

/**
*  accessors
**/

#endif // GRAPHVIEW_H
