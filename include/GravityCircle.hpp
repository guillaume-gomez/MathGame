#ifndef GRAVITYCIRCLE_H
#define GRAVITYCIRCLE_H

#include <SFML/Graphics.hpp>


class GravityCircle : public sf::CircleShape
{
    public:
        GravityCircle(float radius = 1.0f, bool defOrigin = true);
        virtual ~GravityCircle();
        virtual bool isCollide(const sf::FloatRect&);
        void draw(sf::RenderTarget& app);
    protected:

};

#endif // GRAVITYCIRCLE_H
