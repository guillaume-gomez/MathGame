#ifndef IntegralView_H
#define IntegralView_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <list>
#include <vector>

#include <Thor/Shapes.hpp>

#include "IntegralModel.hpp"


class IntegralView
{
    public:
        IntegralView(IntegralModel& model ,const float scale );
        IntegralView();
        virtual ~IntegralView();
        void drawShape(sf::RenderTarget& target);
        void drawLine(sf::RenderTarget& target);
        void representLine();
        void representShape();
    private:
        const IntegralModel& m_model;
        std::vector<sf::RectangleShape> m_lineList;
        std::vector<thor::ConcaveShape> m_shapeList;
        float m_scale;
};

#endif // IntegralView_H
