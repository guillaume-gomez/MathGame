#include "GraphView.hpp"

GraphView::GraphView(ConstrueFunction& model,float thickness, float scale)
:m_isStandAlone(false), m_model(&model),m_thickness(thickness), m_scale(scale), m_graphColor(sf::Color(50,67,135)),
 m_viewport(sf::View())
{}

GraphView::GraphView(float thickness, float scale)
: m_isStandAlone(true), m_model(nullptr), m_thickness(thickness), m_scale(scale), m_graphColor(sf::Color(50,67,135)),
 m_viewport(sf::View())
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
         if( itl->getPosition().x >= m_viewport.getCenter().x - m_viewport.getSize().x
         &&  itl->getPosition().x <= m_viewport.getCenter().x + m_viewport.getSize().x )
         {
            itl->setThickness(m_thickness);
            App.draw(*itl);
         }
	}
}
