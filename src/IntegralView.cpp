#include "IntegralView.hpp"


IntegralView::IntegralView(IntegralModel& model, const float scale)
: m_model(model), m_scale(scale)
{
std::cout << "truc " << model.getListCoordToShapes().size() << std::endl;
std::cout << "ADRESS " << &model << std::endl;
std::cout << "ADRE__SS " << &m_model << std::endl;
}

IntegralView::~IntegralView()
{
    //dtor
}

void IntegralView::represent()
{
std::cout <<"CoteDEV " <<   m_model.getListCoordToShapes().size() << std::endl;
std::cout << "ADS " << &m_model << std::endl;

    for ( std::list<std::list<sf::Vector2f> >::iterator it = m_model.getListCoordToShapes().begin(); it != m_model.getListCoordToShapes().end() ;it++)
    {
    	sf::ConvexShape temp;
                        temp.setPointCount(it->size());
        std::cout << "MACHIN " << std::endl;
        unsigned int i = 0;
    	for (std::list<sf::Vector2f>::iterator itCoordsShape = it->begin(); itCoordsShape != it->end() ; itCoordsShape++)
    	{
            std::cout << "X " << itCoordsShape->x << "Y  " << itCoordsShape->y << std::endl;
    		temp.setPoint(i, *itCoordsShape);
    		//add the scale
    		i++;
    	}

    	// TEMP
    	temp.setOutlineThickness(5);
		temp.setPosition(10, 20);

    	m_shapeList.push_back(temp);
    }
}

void IntegralView::draw(sf::RenderTarget& target)
{
    for (unsigned int i = 0 ; i < m_shapeList.size() ; i++)
    {
          target.draw(m_shapeList[i]);
    }
}
