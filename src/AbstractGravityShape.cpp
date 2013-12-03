#include "AbstractGravityShape.hpp"

AbstractGravityShape::AbstractGravityShape()
{
    //ctor
}

AbstractGravityShape::~AbstractGravityShape()
{
    //dtor
}


void AbstractGravityShape::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}
