#include "IntergralView.hpp"

IntergralView::IntergralView(const IntergralModel& model)
:m_model(model)
{
}

IntergralView::~IntergralView()
{
    //dtor
}
void IntergralView::represent()
{
    for ( std::list<std::list<sf::Vector2f>>::iterator it = m_model.getListCoordToShapes().begin(); it != m_model.getListCoordToShapes().end();it++)
    {
    	sf::ConvexShape temp.setPointCount(it.size());
    	for (std::list<sf::Vector2f>::iterator itCoordsShape = it.begin(), unsigned int i = 0 ; itCoordsShape != it.end() ; itCoordsShape++ ; i++)
    	{
    		temp.setPoint(i, itCoordsShape);
    	}

    	// TEMP
    	polygon.setOutlineThickness(5);
		polygon.setPosition(10, 20);

    	m_shapeList.push_back(temp);
    }
}

void IntergralView::draw(sf::RenderTarget& target)
{
    for (unsigned int i = 0 ; i < m_shapeList.size() ; i++)
    {
          target.draw(m_shapeList[i]);
    }
}
