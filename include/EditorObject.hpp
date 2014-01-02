#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include <string>

#include <SFML/Graphics.hpp>

#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"

/**
@brief : a wrapper class to manage different kind of object circleShape
**/

class EditorObject
{
    public:
        EditorObject();
        virtual ~EditorObject();
        virtual void draw(sf::RenderTarget& app) = 0;
        inline virtual TypeObject getType() const { return m_type;}
        std::string getTypeStr() const ;
        static bool compare(const EditorObject* r1, const EditorObject* r2);
    protected:
    	TypeObject m_type;
    private:
};

#endif // EDITOROBJECT_H
