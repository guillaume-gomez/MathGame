#include "GraphView.hpp"

GraphView::GraphView(ConstrueFunction& model,float thickness, float scale)
:m_isStandAlone(false), m_model(&model),m_thickness(thickness), m_scale(scale), m_graphColor(CurveColor)
{}

GraphView::GraphView(float thickness, float scale)
: m_isStandAlone(true), m_model(nullptr), m_thickness(thickness), m_scale(scale), m_graphColor(CurveColor)
{

}

GraphView::~GraphView()
{
    //dtor
}

void GraphView::represent(float step)
{
	standAloneRepresent(*(this->m_model), step);
}

void GraphView::standAloneRepresent(const ConstrueFunction& model, float step)
{
	m_lines.clear();

	std::list<sf::Vector2f>::const_iterator it = model.m_coords.begin();
	std::list<sf::Vector2f>::const_iterator itNext = model.m_coords.begin();

	if(itNext!=model.m_coords.end())
	{
		itNext++;
	}

	while(itNext!=model.m_coords.end())
	{
		if((itNext->x - it->x) <= step * 2)
		{
			m_lines.push_back(LineSFML2_1(sf::Vector2f(it->x, -it->y) * m_scale, sf::Vector2f(itNext->x, -itNext->y) * m_scale));
			m_lines.rbegin()->setFillColor(m_graphColor);
		}
		it++;
		itNext++;
	}
}

void GraphView::draw(sf::RenderTarget& App)
{
	FOR_STL_ITERATOR(std::list<LineSFML2_1>, m_lines, itl)
	{
		itl->setThickness(m_thickness);
		App.draw(*itl);
	}
}


void GraphView::drawInterval(sf::RenderTarget& App, unsigned int split)
{
    unsigned int increment = 0;
    FOR_STL_ITERATOR(std::list<LineSFML2_1>, m_lines, itl)
	{
		itl->setThickness(m_thickness);
		if(increment == split)
		{
            App.draw(*itl);
            increment = 0;
		}
		increment++;
	}
}
