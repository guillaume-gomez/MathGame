#ifndef IntegralView_H
#define IntegralView_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <list>
#include <vector>
#include "IntegralModel.hpp"

class IntegralView
{
    public:
        IntegralView(IntegralModel& model ,const float scale );
        IntegralView();
        virtual ~IntegralView();
        void draw(sf::RenderTarget& target);
        void represent();
    private:
        const IntegralModel& m_model;
        std::vector<sf::ConvexShape> m_shapeList;
        float m_scale;
};

#endif // IntegralView_H
