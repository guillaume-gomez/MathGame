#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include <SFML/Graphics.hpp>

#include "../libs/ResourcesManagerSFML2_1.hpp"

/**
@brief : a wrapper class to manage different kind of object circleShape
**/

class EditorObject : public sf::CircleShape
{
    public:
        EditorObject();
        virtual ~EditorObject();
        virtual float distance(sf::Vector2f pointOne, sf::Vector2f pointTwo);
        virtual bool isCollide(sf::Vector2f point);
        virtual bool isCollide(const sf::FloatRect& rect);
        virtual void draw(sf::RenderTarget& app);
    protected:
    private:
};

#endif // EDITOROBJECT_H
