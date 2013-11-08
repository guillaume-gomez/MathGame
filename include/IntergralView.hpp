#ifndef INTERGRALVIEW_H
#define INTERGRALVIEW_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <list>
#include <vector>
#include "IntergralModel.hpp"

class IntergralView
{
    public:
        IntergralView(const IntergralModel& model  );
        virtual ~IntergralView();
        void draw(sf::RenderTarget& target);
    private:
        const IntergralModel m_model;
        std::vector<sf::ConvexShape> m_shapeList;
        std::list<sf::Vector2f> m_listPoints;
};

#endif // INTERGRALVIEW_H
