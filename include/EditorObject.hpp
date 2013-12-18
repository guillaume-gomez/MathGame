#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include <SFML/Graphics.hpp>

#include "../libs/ResourcesManagerSFML2_1.hpp"

/**
@brief : a wrapper class to manage different kind of object circleShape
**/

class EditorObject
{
    public:
        EditorObject();
        virtual ~EditorObject();
        virtual void draw(sf::RenderTarget& app);
    protected:
    private:
};

#endif // EDITOROBJECT_H
