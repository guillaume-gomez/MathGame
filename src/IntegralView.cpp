#include "IntegralView.hpp"


IntegralView::IntegralView(IntegralModel& model, const float scale)
: m_model(model), m_scale(scale)
{}

IntegralView::~IntegralView()
{
    //dtor
}

void IntegralView::represent()
{
unsigned int index = 0;
unsigned int i = 0;

    while (i < m_model.getNbPoints() )
    {
        sf::ConvexShape temp;
                        temp.setPointCount(m_model.getNbCoordByShape(index));
        for (unsigned int j = 0; j < m_model.getNbCoordByShape(index); j++)
        {
            temp.setPoint(j, sf::Vector2f(m_model.getCoordToShapes(i).x * m_scale, - m_model.getCoordToShapes(i).y * m_scale));
            //add the scale
         i++;
        }
        // TEMP
        temp.setFillColor(sf::Color(23,20+10*index,20+50*index,100));
        temp.setOutlineColor(sf::Color(0,0,0));
        temp.setOutlineThickness(1);
       // temp.setPosition(10, 20);

        m_shapeList.push_back(temp);
        index++;
    }
}

void IntegralView::draw(sf::RenderTarget& target)
{
    for (unsigned int i = 0 ; i < m_shapeList.size() ; i++)
    {
         target.draw(m_shapeList[i]);
    }
}
