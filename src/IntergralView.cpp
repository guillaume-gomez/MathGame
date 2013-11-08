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
    //to do
}

void IntergralView::draw(sf::RenderTarget& target)
{
    for (unsigned int i = 0 ; i < m_shapeList.size() ; i++)
    {
          target.draw(m_shape[i]);
    }
}
