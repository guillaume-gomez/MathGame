#ifndef ABSTRACTGRAVITYSHAPE_H
#define ABSTRACTGRAVITYSHAPE_H

#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>


class AbstractGravityShape : public thor::ConcaveShape
{
    public:
        AbstractGravityShape();
        virtual ~AbstractGravityShape();
        virtual void draw(sf::RenderTarget& app);
        virtual bool isCollide(const sf::FloatRect&) = 0;
    protected:
    private:
};

#endif // ABSTRACTGRAVITYSHAPE_H
