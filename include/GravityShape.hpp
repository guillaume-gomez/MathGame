#ifndef GRAVITYSHAPE_H
#define GRAVITYSHAPE_H

#include "AbstractGravityShape.hpp"

class GravityShape : public AbstractGravityShape
{
    public:
        GravityShape();
        virtual ~GravityShape();
        virtual bool isCollide(const sf::FloatRect&);
        void addPoints(sf::Vector2f);
        inline unsigned int getNbPoints() const {return this->getNbPoints();}

    protected:
        unsigned int m_nbPoints;
};

#endif // GRAVITYSHAPE_H
