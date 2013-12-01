#include "GraphView.hpp"

GraphView::GraphView(ConstrueFonction& model,float thickness, float scale)
:m_model(model),m_thickness(thickness), m_scale(scale), m_graphColor(sf::Color(50,67,135))
{}

GraphView::~GraphView()
{
    //dtor
}

void GraphView::represent(float step)
{
	m_lines.clear();

	std::list<sf::Vector2f>::const_iterator it = m_model.m_coords.begin();
	std::list<sf::Vector2f>::const_iterator itNext = m_model.m_coords.begin();

	if(itNext!=m_model.m_coords.end())
	{
		itNext++;
	}

	while(itNext!=m_model.m_coords.end())
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

void GraphView::draw(sf::RenderWindow& App)
{
	FOR_STL_ITERATOR(std::list<LineSFML2_1>, m_lines, itl)
	{
		itl->setThickness(m_thickness);
		App.draw(*itl);
	}
}
